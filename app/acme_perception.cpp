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

cv::Mat AcmePerception::drawLabel(const cv::Mat& input_image,
                  std::vector<std::pair<cv::Rect, float>> result) {
  for (size_t i = 0; i < result.size(); ++i) {
    cv::Rect box = result[i].first;
    cv::Point tlc = cv::Point(box.x, box.y);
    // bottom right corner
    cv::Point brc = cv::Point(box.x + box.width, box.y + box.height);
    // draw rectangle for text.
    cv::rectangle(input_image, cv::Point(box.x, box.y - 10),
                  (cv::Point(box.x + box.width, box.y)), cv::Scalar(0, 0, 255),
                  10);
    // draw bounding box
    cv::rectangle(input_image, tlc, brc, cv::Scalar(0, 0, 255), 5);
    // put the label on the black rectangle
    cv::putText(input_image, std::to_string(result[i].second),
                cv::Point(box.x, box.y), cv::FONT_HERSHEY_SIMPLEX, 0.7,
                cv::Scalar(255, 255, 255), 2);
  }
  return input_image;
}

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
  // bool to check if output is saved
  save_data_ = save_data;
}

// Destructor of AcmePerception object
AcmePerception::~AcmePerception() {}

// function for running detection and tracking
void AcmePerception::processInputs() {
  cv::Mat img, output;
  // vector of bounding boxes and their confidence value
  std::vector<std::pair<cv::Rect, float>> detections;
  int counter = 0;
  while (cv::waitKey(1) != 27) {
    img = data_.getInput();
    if (img.empty()) {
      std::cout << "empty image found, exiting";
      break;
    }
    cv::Mat blob = preprocessor_.preProcess(img);
    // vector of bboxes and confidence values
    detections = detector_.detect(blob, img);

    output = drawLabel(img, detections);

    cv::imshow("output", output);

    if (data_.getInputMode() == "images") {
      cv::waitKey(0);
    }
    if (save_data_) {
      data_.writeData(output, std::to_string(counter));
      counter += 1;
    }
  }
}
