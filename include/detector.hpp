#ifndef INCLUDE_DETECTOR_HPP_
#define INCLUDE_DETECTOR_HPP_

#include <opencv2/dnn/dnn.hpp>
#include <opencv2/opencv.hpp>
#include <string>

class Detector {
 public:
  // setupDetector
  Detector();

  ~Detector();

  cv::Mat detect(cv::Mat &blob);

  void logDetectorInfo();

 private:
  // TODO: pull from a config file
  void setupDetector();

  void filterDetections(cv::Mat &input_image, std::vector<cv::Mat> &outputs);

  cv::Mat preProcess(cv::Mat &input_image);

  std::vector<cv::Mat> runInference(cv::Mat &blob);

  cv::Mat NMS(cv::Mat &input_image);

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