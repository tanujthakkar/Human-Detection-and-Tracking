#ifndef INCLUDE_DATA_HPP_
#define INCLUDE_DATA_HPP_

#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

class Data {
 public:
  Data(std::string& mode, std::string& input_path, std::string& output_path);

  ~Data();

  // void setInputMode(std::string& mode);

  std::string getInputMode();

  cv::Mat getInput();

  void writeData(cv::Mat output, std::string name);

 private:
  std::string mode_;

  std::string inputs_path_, outputs_path_;

  std::vector<std::string> inputs_list_;

  cv::VideoCapture cap_;

  cv::VideoWriter videowriter_;

  cv::Mat readImage();

  cv::Mat readStream();
};

#endif
