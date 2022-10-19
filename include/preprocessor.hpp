#ifndef INCLUDE_PREPROCESSOR_H
#define INCLUDE_PREPROCESSOR_H

#include <opencv2/dnn/dnn.hpp>
#include <opencv2/opencv.hpp>

class Preprocessor {
 public:
  Preprocessor();

  ~Preprocessor();

  cv::Mat preProcess(cv::Mat& input_image);

  cv::Size& getInputSize();

 private:
  cv::Size input_size_;
};

#endif