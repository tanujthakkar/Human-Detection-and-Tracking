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

#include <tracker.hpp>

namespace Acme {

Tracker::Tracker() {}

Tracker::~Tracker() { multi_tracker_->clear(); }

void Tracker::track(const cv::Mat& frame,
                    const std::vector<cv::Rect2d>& bboxes) {
  multi_tracker_.release();
  multi_tracker_ =
      cv::legacy::MultiTracker::create();  // Creating tracker from scratch
  for (auto bbox : bboxes) {
    multi_tracker_->add(cv::legacy::TrackerKCF::create(), frame, bbox);
  }
}

void Tracker::update(const cv::Mat& frame) { multi_tracker_->update(frame); }

std::vector<cv::Rect2d> Tracker::getObjects() {
  return multi_tracker_->getObjects();
}

}  // namespace Acme
