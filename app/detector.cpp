#include "detector.hpp"

#include <unistd.h>

#include <fstream>

// TODO: move to appropriate class
const float FONT_SCALE = 0.7;
const int FONT_FACE = cv::FONT_HERSHEY_SIMPLEX;
const int THICKNESS = 1;

cv::Scalar BLACK = cv::Scalar(0, 0, 0);
cv::Scalar BLUE = cv::Scalar(255, 178, 50);
cv::Scalar YELLOW = cv::Scalar(0, 255, 255);
cv::Scalar RED = cv::Scalar(0, 0, 255);

// TODO: move to appropriate class
void draw_label(cv::Mat &input_image, std::string label, int left, int top) {
  // Display the label at the top of the bounding box.
  int baseLine;
  cv::Size label_size =
      cv::getTextSize(label, FONT_FACE, FONT_SCALE, THICKNESS, &baseLine);
  top = std::max(top, label_size.height);
  // Top left corner.
  cv::Point tlc = cv::Point(left, top);
  // Bottom right corner.
  cv::Point brc =
      cv::Point(left + label_size.width, top + label_size.height + baseLine);
  // Draw white rectangle.
  cv::rectangle(input_image, tlc, brc, BLACK, cv::FILLED);
  // Put the label on the black rectangle.
  cv::putText(input_image, label, cv::Point(left, top + label_size.height),
              FONT_FACE, FONT_SCALE, YELLOW, THICKNESS);
}

Detector::Detector() {
  // load params from config
  setupDetector();
}

Detector::~Detector() {}

void Detector::setupDetector() {
  model_path_ = "./../data/YOLOv5s.onnx";

  network_ = cv::dnn::readNet(model_path_);

  input_width_ = 640.0;

  input_height_ = 640.0;

  score_thresh_ = 0.5;

  nms_thresh_ = 0.45;

  confidence_thresh_ = 0.45;

  classes_to_detect_ = {"person"};

  std::string class_names_path = "./../data/coco.names";

  std::ifstream ifs(class_names_path);
  std::string line;
  while (getline(ifs, line)) {
    classes_list_.push_back(line);
  }
}

void Detector::logDetectorInfo() {
  std::cout << "input_height: " << input_height_;
  std::cout << "\ninput_width_: " << input_width_;
  std::cout << "\nscore_thresh_: " << score_thresh_;
  std::cout << "\nnms_thresh_: " << nms_thresh_;
  std::cout << "\nconfidence_thresh_: " << confidence_thresh_;
  std::cout << "\nmodel_path_: " << model_path_;
  std::cout << "\ntotal classes : " << classes_list_.size() << std::endl;
}

cv::Mat Detector::preProcess(cv::Mat &input_image) {
  // Convert to blob.
  cv::Mat blob;
  cv::dnn::blobFromImage(input_image, blob, 1. / 255.,
                         cv::Size(input_width_, input_height_), cv::Scalar(),
                         true, false);

  return blob;
}

std::vector<cv::Mat> Detector::runInference(cv::Mat &blob) {
  std::vector<cv::Mat> outputs;
  network_.setInput(blob);
  network_.forward(outputs, network_.getUnconnectedOutLayersNames());

  return outputs;
}

cv::Mat Detector::detect(cv::Mat &input_image) {
  resetDetector();
  // call pre_process here
  // TODO Use Preprocessor class instance
  cv::Mat blob = preProcess(input_image);

  // call_forward pass here
  std::vector<cv::Mat> detections = runInference(blob);

  // call post_process here
  filterDetections(input_image, detections);

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
    data += 85;
  }
}

cv::Mat Detector::NMS(cv::Mat &input_image) {
  // Perform Non-Maximum Suppression and draw predictions.
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
                  cv::Point(left + width, top + height), BLUE, 3 * THICKNESS);
    // Get the label for the class name and its confidence.
    std::string label = cv::format("%.2f", confidences_[idx]);
    label = classes_list_[class_ids_[idx]] + ":" + label;
    // Draw class labels.
    draw_label(input_image, label, left, top);
  }
  return input_image;
}

void Detector::resetDetector() {
  class_ids_.clear();
  confidences_.clear();
  bboxes_.clear();
}
