#ifndef INCLUDE_DETECTOR_HPP_
#define INCLUDE_DETECTOR_HPP_

#include <opencv2/dnn/dnn.hpp>
#include <opencv2/opencv.hpp>
#include <string>

class Detector {
 public:

  Detector();

  ~Detector();

  cv::Mat detect(cv::Mat &input_blob, cv::Mat &input_image);

  void setInputSize(const cv::Size size);

  void setScoreThreshold(const double score_thresh);

  void setConfidenceThreshold(const double conf_thresh);

  void setNMSThreshold(const double nms_thresh);

  void setClassesToDetect(const std::vector<std::string> classes);

  void setModelPath(const std::string model_path);

  void setClassList(const std::string class_list_path);

 private:

  void filterDetections(cv::Mat &input_image, std::vector<cv::Mat> &outputs);

  std::vector<cv::Mat> runInference(cv::Mat &blob);

  cv::Mat NMS(cv::Mat &input_image);

  void drawLabel(cv::Mat &input_image, std::string label, int left, int top);

  void resetDetector();

  std::string model_path_;

  cv::dnn::Net network_;

  double input_width_;

  double input_height_;

  double score_thresh_;

  double nms_thresh_;

  double confidence_thresh_;

  std::vector<int> class_ids_;

  std::vector<float> confidences_;

  std::vector<cv::Rect> bboxes_;

  std::vector<std::string> classes_list_;

  std::vector<std::string> classes_to_detect_;
};

#endif