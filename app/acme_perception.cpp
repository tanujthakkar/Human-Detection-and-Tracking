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
 * @file acme_perception.cpp
 * @author Nitesh Jha (Driver), Tanuj Thakkar (Navigator)
 * @brief file containing AcmePerception definition
 * @version 0.1
 * @date 2022-10-19
 *
 *
 */

#include <acme_perception.hpp>

namespace Acme {

// Constuctor for initializing object with input mode, input path, and output
// path
AcmePerception::AcmePerception(const std::string& mode,
                               const std::string& input_path,
                               const std::string& output_path,
                               const bool& save_data) {
  // set data input mode to images or stream
  data_.setInputMode(mode);
  // set input and outpath path dir
  data_.setIOpaths(input_path, output_path);
  // setup data read and write members
  data_.initialize();
  // set list of classes to be detected by model
  std::vector<std::string> classes{"person"};
  detector_.setClassesToDetect(classes);
  // set model path of detector
  detector_.setModelPath("./data/models/YOLOv5s.onnx");
  // set list of all class labels detected by detector
  detector_.setClassList("./data/models/coco.names");

  Eigen::Matrix4d extrinsics;
  extrinsics << 1, 0, 0, 0.25, 0, 1, 0, 0.00, 0, 0, 1, 0.05, 0, 0, 0, 1;
  transformer_.initialize(1200, extrinsics,
                          1.7);  // Initializing transformer private members

  // bool to check if output is saved
  save_data_ = save_data;
}

// Destructor of AcmePerception object
AcmePerception::~AcmePerception() {}

// function for running detection and tracking
void AcmePerception::processInputs(const bool& visualize) {
  cv::Mat img;
  cv::Mat output;
  int counter = 0;
  size_t detected = 0;
  std::vector<cv::Rect2d> bboxes;
  std::vector<cv::Rect2d> tracker_bboxes;
  std::vector<std::pair<cv::Rect, float>> detections;
  std::vector<Eigen::Vector4d> positions;

  while (cv::waitKey(1) != 27) {
    img = data_.getInput();
    output = img.clone();
    if (img.empty()) {
      std::cout << "EMPTY IMAGE FOUND, EXITING" << std::endl;
      return;
    }

    cv::Mat blob = preprocessor_.preProcess(img);
    detections = detector_.detect(blob, img);

    // Add detection bounding boxes
    bboxes.clear();
    for (size_t i = 0; i < detections.size(); i++) {
      bboxes.push_back(detections[i].first);
    }

    if (data_.getInputMode() == "stream") {
      if (detected != detections.size() && detections.size() > 0) {
        tracker_.track(img, bboxes);
        detected = detections.size();
      }
      if (detections.size() > 0) {
        tracker_.update(img);
        tracker_bboxes = tracker_.getObjects();
        positions = transformer_.calculatePositions(tracker_bboxes);
        drawLabel(output, tracker_bboxes, positions);
      }
    } else {
      drawLabel(output, bboxes);
    }

    if (visualize) cv::imshow("Acme Perception", output);  // Display output

    if (data_.getInputMode() == "images") {
      cv::waitKey(0);
    }
    if (save_data_) {
      data_.writeData(output, std::to_string(counter));
      counter += 1;
    }
  }
}

cv::Mat AcmePerception::drawLabel(
    const cv::Mat& input_image, const std::vector<cv::Rect2d>& bboxes,
    const std::vector<Eigen::Vector4d>& positions) {
  for (size_t i = 0; i < bboxes.size(); ++i) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << "ID:" << (i + 1) << "("
           << positions[i][0] << "," << positions[i][1] << ","
           << positions[0][2] << ")";
    std::string label = stream.str();
    // std::string label = std::to_string(static_cast<int>(i+1)) + "(" +
    // std::to_string(static_cast<float>(positions[i][0])) + "," +
    // std::to_string(static_cast<float>(positions[i][1])) + "," +
    // std::to_string(static_cast<float>(positions[i][2])) + ")";
    cv::putText(input_image, label, cv::Point(bboxes[i].x + 15, bboxes[i].y),
                cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, cv::Scalar(0, 0, 255));
    cv::rectangle(input_image, bboxes[i], cv::Scalar(0, 0, 255), 2, 1);
  }
  return input_image;
}

cv::Mat AcmePerception::drawLabel(const cv::Mat& input_image,
                                  const std::vector<cv::Rect2d>& bboxes) {
  for (size_t i = 0; i < bboxes.size(); ++i) {
    cv::rectangle(input_image, bboxes[i], cv::Scalar(0, 0, 255), 2, 1);
  }
  return input_image;
}

}  // namespace Acme
