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
 * @file transformer.cpp
 * @author Tanuj Thakkar (Driver), Nitesh Jha (Navigator)
 * @brief source file for Transformer class
 * @version 0.1
 * @date 2022-10-28
 *
 *
 */

#include <transformer.hpp>

namespace Acme {

Transformer::Transformer(const double& focal_length, const Eigen::Matrix4d& extrinsics, const double& avg_human_height) {
  camera_.setFocalLength(focal_length);
  camera_.setExtrinsics(extrinsics);
  avg_human_height_ =
      avg_human_height;  // Initializing avg_human_height (scale factor)
}

Transformer::~Transformer() {}

std::vector<Eigen::Vector4d> Transformer::calculatePositions(
    const std::vector<cv::Rect2d>& bboxes) {
  std::vector<Eigen::Vector4d> positions;

  Eigen::Vector4d C;  // Center of bounding box in camera frame
  Eigen::Vector4d R;  // Position in robot frame
  // Iterating over each detection
  for (auto bbox : bboxes) {
    double estimated_depth =
        (camera_.getFocalLength() / bbox.height) *
        avg_human_height_;  // Estimated depth with respect to scale assumption
    double factor = estimated_depth / camera_.getFocalLength();

    double C_X =
        factor *
        (bbox.x +
         (bbox.width / 2));  // X coordinate of detected human in camera frame
    double C_Y =
        factor *
        (bbox.y +
         (bbox.height / 2));  // Y coordinate of detected human in camera frame
    C << C_X, C_Y, estimated_depth, 1;

    R = camera_.getExtrinsics().inverse() * C;  // Detected human in robot frame
    positions.push_back(R);  // Pushing back position in robot frame
  }

  return positions;
}

}  // namespace Acme
