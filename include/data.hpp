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
 * @file data.hpp
 * @author Nitesh Jha (Driver), Tanuj Thakkar (Navigator)
 * @brief header file for Data class
 * @version 0.1
 * @date 2022-10-19
 *
 *
 */
#ifndef INCLUDE_DATA_HPP_
#define INCLUDE_DATA_HPP_

#include <string>
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>

class Data {
 public:
  /**
   * @brief Constructor for Data object
   *
   * @param mode input mode. Valid modes: "images", "stream"
   * @param input_path path to dir of inputs
   * @param output_path path to dir for saving outputs
   */
  Data(const std::string& mode, const std::string& input_path,
       const std::string& output_path);

  /**
   * @brief Constructor for Data object
   *
   */
  Data();

  /**
   * @brief Destructor for Data object
   *
   */
  ~Data();

  /**
   * @brief Set the Input mode for processing
   *
   * @param mode images/stream
   */
  void setInputMode(const std::string& mode);

  /**
   * @brief Set paths to input dir and output dir
   *
   * @param input_path
   * @param output_path
   */
  void setIOpaths(const std::string& input_path,
                  const std::string& output_path);

  /**
   * @brief Get the input Mode: images/stream
   *
   * @return std::string mode:images/stream
   */
  std::string getInputMode();

  /**
   * @brief Get image for processing from either a image dir or a stream
   *
   * @return cv::Mat image
   */
  cv::Mat getInput();

  /**
   * @brief write output to output dir: images or make video file if
   * mode=="stream"
   *
   * @param output image to write
   * @param name name of output
   */
  void writeData(cv::Mat output, const std::string& name);

 private:
  // Input mode
  std::string mode_;

  // input and output paths
  std::string inputs_path_, outputs_path_;

  // list of input images if mode =="images"
  std::vector<std::string> inputs_list_;

  // object to read stream data
  cv::VideoCapture cap_;

  // object to write stream data
  cv::VideoWriter videowriter_;

  /**
   * @brief Read image from inputs_paths_ dir
   *
   * @return cv::Mat image
   */
  cv::Mat readImage();

  /**
   * @brief Read a frame from stream
   *
   * @return cv::Mat
   */
  cv::Mat readStream();
};

#endif  // INCLUDE_DATA_HPP_
