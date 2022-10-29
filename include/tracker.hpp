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
 * @author Tanuj Thakkar (Driver), Nitesh Jha (Navigator)
 * @brief header file for Tracker class
 * @version 0.1
 * @date 2022-10-26
 *
 *
 */

#ifndef INCLUDE_TRACKER_HPP_
#define INCLUDE_TRACKER_HPP_

#pragma once

#include <vector>

#include <opencv2/core/cvstd_wrapper.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/tracking/tracking_legacy.hpp>

namespace Acme {

class Tracker {
 public:
  /**
   * @brief Construct a new Tracker object
   * 
   */
  Tracker();  // Default constructor

  /**
   * @brief Destroy the Tracker object
   * 
   */
  ~Tracker();  // Default destructor

  /**
   * @brief Setup trackers of the cv::MultiTracker object
   * 
   * @param frame 
   * @param bboxes 
   */
  void track(
      const cv::Mat& frame,
      const std::vector<cv::Rect2d>& bboxes);

  /**
   * @brief Update the trackers with respect to frame
   * 
   * @param frame 
   */
  void update(const cv::Mat& frame);

  /**
   * @brief Get the Objects object
   * 
   * @return std::vector<cv::Rect2d> 
   */
  std::vector<cv::Rect2d> getObjects();

 private:
  cv::legacy::MultiTracker multi_tracker_;
};

}  // namespace Acme

#endif  // INCLUDE_TRACKER_HPP_
