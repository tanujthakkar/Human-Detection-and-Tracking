#include "detector.hpp"

#include <unistd.h>

#include <fstream>

Detector::Detector() {
}

Detector::~Detector() {}

void Detector::setInputSize(const cv::Size size){
  input_width_ = size.width;
  input_height_ = size.height; 
}

void Detector::setScoreThreshold(const double score_thresh){
  score_thresh_ = score_thresh;
}

void Detector::setConfidenceThreshold(const double conf_thresh){
  confidence_thresh_ = conf_thresh;
}

void Detector::setNMSThreshold(const double nms_thresh){
  nms_thresh_ = nms_thresh;
}

void Detector::setClassesToDetect(const std::vector<std::string> classes){
  classes_to_detect_ = classes;
}

void Detector::setModelPath(const std::string model_path){
  model_path_ = model_path;
  network_ = cv::dnn::readNet(model_path_);
}

void Detector::setClassList(const std::string class_list_path){
  std::ifstream ifs(class_list_path);
  std::string line;
  while (getline(ifs, line)) {
    classes_list_.push_back(line);
  }

}

std::vector<cv::Mat> Detector::runInference(cv::Mat &blob) {
  std::vector<cv::Mat> outputs;
  network_.setInput(blob);
  network_.forward(outputs, network_.getUnconnectedOutLayersNames());

  return outputs;
}

cv::Mat Detector::detect(cv::Mat &input_blob, cv::Mat &input_image) {
  resetDetector();

  // Forward Pass
  std::vector<cv::Mat> detections = runInference(input_blob);

  // Filter low confidence detections and low class scores, and keep only classes_to_detect
  filterDetections(input_image, detections);

  // Non-maximum suppression
  cv::Mat result = NMS(input_image);

  return result;
}

void Detector::filterDetections(cv::Mat &input_image,
                                std::vector<cv::Mat> &outputs) {
  // Resizing factor.
  float ratio_x = input_image.cols / input_width_;
  float ratio_y = input_image.rows / input_height_;
  float *data = (float *)outputs[0].data;
  const int dimensions = 85;
  // 25200 for default size 640.
  const int rows = 25200;
  // Iterate through 25200 detections.
  for (int i = 0; i < rows; ++i) {
    float confidence = data[4];
    // Discard bad detections and continue.
    if (confidence >= confidence_thresh_) {
      float *classes_scores = data + 5;
      // Create a 1x85 Mat and store class scores of 80 classes.
      cv::Mat scores(1, classes_list_.size(), CV_32FC1, classes_scores);
      // Perform minMaxLoc and acquire the index of best class  score.
      cv::Point class_id;
      double max_class_score;
      cv::minMaxLoc(scores, 0, &max_class_score, 0, &class_id);
      // Continue if the class score is above the threshold.
      if (max_class_score > score_thresh_ &&
          std::find(classes_to_detect_.begin(), classes_to_detect_.end(),
                    classes_list_[class_id.x]) != classes_to_detect_.end()) {
        // Store class ID and confidence in the pre-defined respective vectors.
        confidences_.push_back(confidence);
        class_ids_.push_back(class_id.x);
        // Center.
        float cx = data[0];
        float cy = data[1];
        // Box dimension.
        float w = data[2];
        float h = data[3];
        // Bounding box coordinates.
        int left = int((cx - 0.5 * w) * ratio_x);
        int top = int((cy - 0.5 * h) * ratio_y);
        int width = int(w * ratio_x);
        int height = int(h * ratio_y);
        // Store good detections in the boxes vector.
        bboxes_.push_back(cv::Rect(left, top, width, height));
      }
    }
    // Jump to the next row.
    data += dimensions;
  }
}

cv::Mat Detector::NMS(cv::Mat &input_image) {
  std::vector<int> indices;
  cv::dnn::NMSBoxes(bboxes_, confidences_, score_thresh_, nms_thresh_, indices);
  for (int i = 0; i < indices.size(); i++) {
    int idx = indices[i];
    cv::Rect box = bboxes_[idx];
    int left = box.x;
    int top = box.y;
    int width = box.width;
    int height = box.height;
    // Draw bounding box.
    cv::rectangle(input_image, cv::Point(left, top),
                  cv::Point(left + width, top + height), cv::Scalar(255, 178, 50), 3);
    // Get the label for the class name and its confidence.
    std::string label = cv::format("%.2f", confidences_[idx]);
    label = classes_list_[class_ids_[idx]] + ":" + label;
    // Draw class labels.
    drawLabel(input_image, label, left, top);
  }
  return input_image;
}

void Detector::drawLabel(cv::Mat &input_image, std::string label, int left, int top) {
  // Display the label at the top of the bounding box.
  int baseLine;
  cv::Size label_size =
      cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.7, 1, &baseLine);
  top = std::max(top, label_size.height);
  // Top left corner.
  cv::Point tlc = cv::Point(left, top);
  // Bottom right corner.
  cv::Point brc =
      cv::Point(left + label_size.width, top + label_size.height + baseLine);
  // Draw white rectangle.
  cv::rectangle(input_image, tlc, brc, cv::Scalar(0, 0, 0), cv::FILLED);
  // Put the label on the black rectangle.
  cv::putText(input_image, label, cv::Point(left, top + label_size.height),
              cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 255, 255), 1);
}

void Detector::resetDetector() {
  class_ids_.clear();
  confidences_.clear();
  bboxes_.clear();
}
