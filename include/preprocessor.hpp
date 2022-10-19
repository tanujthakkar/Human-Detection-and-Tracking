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
 * @file preprocessor.hpp
 * @author Nitesh Jha (Driver), Tanuj Thakkar (Navigator)
 * @brief header file for Preprocessor class
 * @version 0.1
 * @date 2022-10-19
 *
 *
 */
#ifndef INCLUDE_PREPROCESSOR_H
#define INCLUDE_PREPROCESSOR_H

#include <opencv2/dnn/dnn.hpp>
#include <opencv2/opencv.hpp>

class Preprocessor {
 public:
  /**
   * @brief Constructor for Preprocessor object
   *
   */
  Preprocessor();

  /**
   * @brief Destructor for Preprocessor object
   *
   */
  ~Preprocessor();

  /**
   * @brief preprocess input image which includes resizing and blob generation
   *
   * @param input_image
   * @return cv::Mat
   */
  cv::Mat preProcess(cv::Mat& input_image);

  /**
   * @brief Get the input size required by the detector model
   *
   * @return cv::Size&
   */
  cv::Size& getInputSize();

 private:
  // size required by detector model
  cv::Size input_size_;
};

#endif