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
 * @file camera.hpp
 * @author Tanuj Thakkar (Driver), Nitesh Jha (Navigator)
 * @brief header file for Camera class
 * @version 0.1
 * @date 2022-10-28
 *
 *
 */

#ifndef INCLUDE_CAMERA_HPP_
#define INCLUDE_CAMERA_HPP_

#pragma once

#include <Eigen/Dense>

namespace Acme {

class Camera {
 public:
  /**
   * @brief Construct a new Camera object
   *
   */
  Camera();

  /**
   * @brief Construct a new Camera object
   *
   * @param focal_length Focal length of the camera
   * @param extrinsics Extrinsics, i.e., transformation from robot frame to
   * camera frame
   */
  Camera(const double& focal_length, const Eigen::Matrix4d& extrinsics);

  /**
   * @brief Destroy the Camera object
   *
   */
  ~Camera();

  /**
   * @brief Get the Focal Length object
   *
   * @return double
   */
  double getFocalLength() const;

  /**
   * @brief Get the Extrinsics object
   *
   * @return Eigen::Matrix4d
   */
  Eigen::Matrix4d getExtrinsics() const;

  /**
   * @brief Set the Focal Length object
   *
   * @param focal_length
   */
  void setFocalLength(const double& focal_length);

  /**
   * @brief Set the Extrinsics object
   *
   * @param extrinsics
   */
  void setExtrinsics(const Eigen::Matrix4d& extrinsics);

 private:
  double focal_length_;         // Focal length of the camera
  Eigen::Matrix4d extrinsics_;  // Extrinsics, i.e., transformation from robot
                                // frame to camera frame
};

}  // namespace Acme

#endif  // INCLUDE_CAMERA_HPP_
