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
 * @file data.cpp
 * @author Nitesh Jha (Driver), Tanuj Thakkar (Navigator)
 * @brief file containing Data class definition
 * @version 0.1
 * @date 2022-10-19
 *
 *
 */
#include <data.hpp>

/**
 * @brief Constructor for Data object
 *
 */
Data::Data() {}

/**
 * @brief Constructor for Data object with mode, input and output paths
 *
 * @param mode images/stream
 * @param input_path input images dir
 * @param output_path output dir
 */
Data::Data(const std::string& mode, const std::string& input_path,
           const std::string& output_path)
    : mode_(mode), inputs_path_(input_path), outputs_path_(output_path) {
  initialize();
}

void Data::initialize() {
  if (mode_ == "images") {
    // populate list of images from input dir
    cv::glob(inputs_path_, inputs_list_);
  } else if (mode_ == "stream") {
    // Open VideoCapture object
    cap_.open(0);
    // width of frame
    int frame_width = cap_.get(cv::CAP_PROP_FRAME_WIDTH);
    // height of frame
    int frame_height = cap_.get(cv::CAP_PROP_FRAME_HEIGHT);
    // initialize videowriter object for saving output
    videowriter_ = cv::VideoWriter(outputs_path_ + "output.avi",
                                   cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
                                   10, cv::Size(frame_width, frame_height));
    if (!cap_.isOpened()) {
      // Fail to open stream device
      std::cout << "\nCannot open input camera!\n";
    }
  }
}

Data::~Data() {
  // close camera if open and save video output of stream
  if (mode_ == "stream" && cap_.isOpened()) {
    cap_.release();
    videowriter_.release();
  }
}

// set input mode to either images or stream
void Data::setInputMode(const std::string& mode) { mode_ = mode; }

// set input and output paths
void Data::setIOpaths(const std::string& input_path,
                      const std::string& output_path) {
  inputs_path_ = input_path;
  outputs_path_ = output_path;
}

// get mode of input
std::string Data::getInputMode() { return mode_; }

// read an image either from stream or image dir
cv::Mat Data::getInput() {
  // return 0th image and pop(0)
  if (mode_ == "images") {
    return readImage();
  } else if (mode_ == "stream") {
    return readStream();
  } else {
    return cv::Mat();
  }
}

// read image from dir
cv::Mat Data::readImage() {
  if (inputs_list_.empty()) return cv::Mat();
  cv::Mat img = cv::imread(inputs_list_.back());
  inputs_list_.pop_back();
  return img;
}

// read frame from stream
cv::Mat Data::readStream() {
  cv::Mat img;
  cap_.read(img);
  return img;
}

// save output image with a specified name
void Data::writeData(cv::Mat output, const std::string& name) {
  if (mode_ == "images") {
    cv::imwrite(outputs_path_ + name + ".jpg", output);
  } else if (mode_ == "stream") {
    videowriter_.write(output);
  }
}
