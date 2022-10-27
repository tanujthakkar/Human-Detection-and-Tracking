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
 * @file acme_perception.hpp
 * @author Nitesh Jha (Driver), Tanuj Thakkar (Navigator)
 * @brief header file for AcmePerception class
 * @version 0.1
 * @date 2022-10-19
 *
 *
 */
#ifndef INCLUDE_ACME_PERCEPTION_HPP_
#define INCLUDE_ACME_PERCEPTION_HPP_

#include<string>
#include <vector>
#include <utility>
#include <data.hpp>
#include <detector.hpp>
#include <preprocessor.hpp>

class AcmePerception {
 public:
  /**
   * @brief Constructor for AcmePerception object
   *
   * @param mode input mode for detection. Valid modes: "images", "stream"
   * @param input_path path to dir of inputs if mode is"images"
   * @param output_path path to dir for saving outputs
   */
  AcmePerception(const std::string& mode, const std::string& input_path,
                 const std::string& output_path, const bool& save_data);

  /**
   * @brief Destrctor for AcmePerception object
   *
   */
  ~AcmePerception();

  /**
   * @brief process input image/stream to obtain detection and track them
   *
   */
  void processInputs();

  /**
   * @brief Draw output of detection and tracking
   * 
   * @param input_image 
   * @param boxes 
   * @return cv::Mat 
   */
  cv::Mat drawLabel(const cv::Mat& input_image,
                  std::vector<std::pair<cv::Rect, float>> boxes);

 private:
  /**
   * @brief  Detector object
   *
   */
  Detector detector_;

  /**
   * @brief Preprocessor object
   *
   */
  Preprocessor preprocessor_;

  /**
   * @brief Data object
   *
   */

  Data data_;

  // To record the input
  bool save_data_;
};

#endif  // INCLUDE_ACME_PERCEPTION_HPP_
