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
#ifndef INCLUDE_ACME_PERCEPTION_HPP
#define INCLUDE_ACME_PERCEPTION_HPP

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
  AcmePerception(std::string& mode, std::string& input_path,
                 std::string& output_path);

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
};

#endif