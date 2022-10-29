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
 * @file transformer.hpp
 * @author Tanuj Thakkar (Driver), Nitesh Jha (Navigator)
 * @brief header file for Transformer class
 * @version 0.1
 * @date 2022-10-28
 *
 *
 */

#ifndef INCLUDE_TRANSFORMER_HPP_
#define INCLUDE_TRANSFORMER_HPP_

#pragma once

#include <vector>
#include <opencv2/core/types.hpp>
#include <camera.hpp>

namespace Acme {

class Transformer {
 public:
  /**
   * @brief Construct a new Transformer object
   *
   */
  Transformer();

  /**
   * @brief Construct a new Transformer object
   *
   * @param camera
   * @param avg_human_height
   */
  Transformer(const double& focal_length, const Eigen::Matrix4d& extrinsics,
              const double& avg_human_height);

  /**
   * @brief Destroy the Transformer object
   *
   */
  ~Transformer();

  /**
   * @brief Initialize private members
   *
   * @param focal_length
   * @param extrinsics
   * @param avg_human_height
   */
  void initialize(const double& focal_length, const Eigen::Matrix4d& extrinsics,
                  const double& avg_human_height);

  /**
   * @brief Method to calculate poisitions of humans in robot frame
   *
   * @param bboxes Bounding boxes being tracked
   * @return std::vector<Eigen::Vector4d> Positions in robot frame
   */
  std::vector<Eigen::Vector4d> calculatePositions(
      const std::vector<cv::Rect2d>& bboxes);

 private:
  Camera camera_;            // Camera object
  double avg_human_height_;  // Average human height for scaling factor
};

}  // namespace Acme

#endif  // INCLUDE_TRANSFORMER_HPP_
