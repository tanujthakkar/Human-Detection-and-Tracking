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
 * @file camera.cpp
 * @author Tanuj Thakkar (Driver), Nitesh Jha (Navigator)
 * @brief source file for Camera class
 * @version 0.1
 * @date 2022-10-28
 *
 *
 */

#include <camera.hpp>

namespace Acme {

Camera::Camera() {}

Camera::Camera(const double& focal_length, const Eigen::Matrix4d& extrinsics) {
  focal_length_ = focal_length;
  extrinsics_ = extrinsics;
}

Camera::~Camera() {}

double Camera::getFocalLength() const { return focal_length_; }

Eigen::Matrix4d Camera::getExtrinsics() const { return extrinsics_; }

void Camera::setFocalLength(const double& focal_length) {
  focal_length_ = focal_length;
}

void Camera::setExtrinsics(const Eigen::Matrix4d& extrinsics) {
  extrinsics_ = extrinsics;
}

}  // namespace Acme
