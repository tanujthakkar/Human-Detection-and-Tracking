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
 * @file preprocessor.cpp
 * @author Nitesh Jha (Driver), Tanuj Thakkar (Navigator)
 * @brief file containing Preprocessor class definition
 * @version 0.1
 * @date 2022-10-19
 *
 *
 */
#include "preprocessor.hpp"

// Constructor for object with input size for detector model
Preprocessor::Preprocessor() : input_size_(cv::Size(640.0, 640.0)) {}

// Destructor for object
Preprocessor::~Preprocessor() {}

// run preprocessing of input image for input to detector model
cv::Mat Preprocessor::preProcess(cv::Mat& input_image) {
  cv::Mat blob;
  // generate blob
  cv::dnn::blobFromImage(input_image, blob, 1. / 255., input_size_,
                         cv::Scalar(), true, false);

  return blob;
}

// return size that is used for preprocessing
cv::Size& Preprocessor::getInputSize() { return input_size_; }
