/******************************************************************************
 * MIT License

Copyright (c) 2022 Nitesh Jha, Tanuj Thakkar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
* *******************************************************************************
*/

/**
 * @copyright Copyright (c) 2022 Nitesh Jha, Tanuj Thakkar
 * @file detector.hpp
 * @author Nitesh Jha (Driver), Tanuj Thakkar (Navigator)
 * @brief header file for Detector class
 * @version 0.1
 * @date 2022-10-19
 *
 *
 */
#ifndef INCLUDE_DETECTOR_HPP_
#define INCLUDE_DETECTOR_HPP_

#include <string>
#include <vector>
#include <utility>
#include <opencv2/dnn/dnn.hpp>
#include <opencv2/opencv.hpp>


namespace Acme {

class Detector {
 public:
  /**
   * @brief Constructor for Detector object
   *
   */
  Detector();

  /**
   * @brief Destructor for Detector object
   *
   */
  ~Detector();

  /**
   * @brief run detection and filtering on the input blob
   *
   * @param input_blob blob generated from image
   * @param input_image input image from which blob was generated
   * @return cv::Mat output image with labels, bounding box and confidence
   * scores
   */
  std::vector<std::pair<cv::Rect, float>> detect(const cv::Mat &input_blob,
                                                 const cv::Mat &input_image);

  /**
   * @brief Set the Input Size for detection model
   *
   * @param size
   */
  void setInputSize(const cv::Size& size);

  /**
   * @brief Set the class score threshold for filtering detections
   *
   * @param score_thresh double: score threshold
   */
  void setScoreThreshold(const double& score_thresh);

  /**
   * @brief Set the confidence threshold to filter out low confidence detections
   *
   * @param conf_thresh confidence threshold
   */
  void setConfidenceThreshold(const double& conf_thresh);

  /**
   * @brief set threshold for Non-Maximum-Suppression
   *
   * @param nms_thresh
   */
  void setNMSThreshold(const double& nms_thresh);

  /**
   * @brief Set the list of classes to detect using the detector model
   *
   * @param classes vector<string> containing list of classes to detect
   */
  void setClassesToDetect(const std::vector<std::string> &classes);

  /**
   * @brief Set the detector model path
   *
   * @param model_path path to model
   */
  void setModelPath(const std::string &model_path);

  /**
   * @brief Populate list of all classes for the detector model
   *
   * @param class_list_path
   */
  void setClassList(const std::string &class_list_path);

 private:
  /**
   * @brief filter out low confidence detections, detections with low class
   * scores, and retain ones that we want to detect
   *
   * @param input_image
   * @param outputs
   */
  void filterDetections(const cv::Mat &input_image,
                        const std::vector<cv::Mat> &outputs);

  /**
   * @brief Forward pass through the detector model
   *
   * @param blob input blob generated from input image
   * @return std::vector<cv::Mat>
   */
  std::vector<cv::Mat> runInference(const cv::Mat &blob);

  /**
   * @brief Perform Non-maximum-suppression to filter overlapping boxes
   *
   * @param input_image
   * @return cv::Mat
   */
  std::vector<std::pair<cv::Rect, float>> NMS();

  /**
   * @brief clear variables stored after a detection: bounding box vectors,
   * confidence vectors, class_labels vector
   *
   */
  void resetDetector();

  // model path for detector
  std::string model_path_;

  // network
  cv::dnn::Net network_;

  // width of input that is expected by detector
  double input_width_;

  // height of input that is expected by detector
  double input_height_;

  // score threshold
  double score_thresh_;

  // NMS threshold
  double nms_thresh_;

  // confidence threshold
  double confidence_thresh_;

  // ist of class IDs that is detected in image
  std::vector<int> class_ids_;

  // vector of confidence values of classes detected in image
  std::vector<float> confidences_;

  // vector of bboxes detected in images
  std::vector<cv::Rect> bboxes_;

  // vector of all class labels of detector
  std::vector<std::string> classes_list_;

  // vector of class labels that should be detected
  std::vector<std::string> classes_to_detect_;
};

}  // namespace Acme

#endif  // INCLUDE_DETECTOR_HPP_
