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

// Constuctor for initializing object with input mode, input path, and output
// path
AcmePerception::AcmePerception(std::string& mode, std::string& input_path,
                               std::string& output_path) {
  // set data input mode to images or stream
  data_.setInputMode(mode);
  // set input and outpath path dir
  data_.setIOpaths(input_path, output_path);
  // set size of input for the detector model
  detector_.setInputSize(cv::Size(640, 640));
  // set score threshold for detections
  detector_.setScoreThreshold(0.5);
  // set confidence threshold for detections
  detector_.setConfidenceThreshold(0.45);
  // set NMS threshold
  detector_.setNMSThreshold(0.5);
  // set list of classes to be detected by model
  std::vector<std::string> classes {"person"};
  detector_.setClassesToDetect(classes);
  // set model path of detector
  detector_.setModelPath("./../data/models/YOLOv5s.onnx");
  // set list of all class labels detected by detector
  detector_.setClassList("./../data/models/coco.names");
  }

  // Destructor of AcmePerception object
  AcmePerception::~AcmePerception() {}

  // function for running detection and tracking
  void AcmePerception::processInputs() {
    cv::Mat img, output;
    bool save_output = false;
    int counter = 0;
    while (cv::waitKey(1) != 27) {
      img = data_.getInput();
      if (img.empty()) {
        std::cout << "empty image found, exiting";
        break;
      }
      cv::Mat blob = preprocessor_.preProcess(img);
      output = detector_.detect(blob, img);

      cv::imshow("output", output);
      cv::waitKey(0);
      if (save_output) {
        data_.writeData(output, std::to_string(counter));
        counter += 1;
      }
    }
  }