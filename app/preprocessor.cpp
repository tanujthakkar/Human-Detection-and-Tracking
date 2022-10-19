#include "preprocessor.hpp"

Preprocessor::Preprocessor() : input_size_(cv::Size(640.0, 640.0)) {}

Preprocessor::~Preprocessor() {}

cv::Mat Preprocessor::preProcess(cv::Mat& input_image) {
  cv::Mat blob;
  cv::dnn::blobFromImage(input_image, blob, 1. / 255., input_size_,
                         cv::Scalar(), true, false);

  return blob;
}

cv::Size& Preprocessor::getInputSize() { return input_size_; }
