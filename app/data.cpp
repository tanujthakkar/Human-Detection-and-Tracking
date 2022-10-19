#include "data.hpp"

Data::Data(std::string& mode, std::string& input_path, std::string& output_path)
    : mode_(mode), inputs_path_(input_path), outputs_path_(output_path) {
  if (mode_ == "images") {
    cv::glob(inputs_path_, inputs_list_);
  }

  else if (mode_ == "stream") {
    cap_.open(0);
    int frame_width = cap_.get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = cap_.get(cv::CAP_PROP_FRAME_HEIGHT);
    videowriter_ = cv::VideoWriter(outputs_path_ + "output.avi",
                                   cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
                                   10, cv::Size(frame_width, frame_height));
    if (!cap_.isOpened()) {
      std::cout << "\nCannot open input camera!\n";
    }
  }
}

Data::~Data() {
  // close camera if open
  if (mode_ == "stream" && cap_.isOpened()) {
    cap_.release();
    videowriter_.release();
  }
}

std::string Data::getInputMode() { return mode_; }

cv::Mat Data::getInput() {
  // return 0th image and pop(0)
  if (mode_ == "images") {
    return readImage();
  } else if (mode_ == "stream") {
    return readStream();
  }

  else
    return cv::Mat();
}

cv::Mat Data::readImage() {
  if (inputs_list_.empty()) return cv::Mat();
  cv::Mat img = cv::imread(inputs_list_.back());
  inputs_list_.pop_back();
  return img;
}

cv::Mat Data::readStream() {
  cv::Mat img;
  cap_.read(img);
  return img;
}

void Data::writeData(cv::Mat output, std::string name) {
  if (mode_ == "images") {
    cv::imwrite(outputs_path_ + name + ".jpg", output);
  } else if (mode_ == "stream") {
    videowriter_.write(output);
  }
}
