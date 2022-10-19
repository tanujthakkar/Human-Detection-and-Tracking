#include <gtest/gtest.h>

#include "detector.hpp"
#include "preprocessor.hpp"
#include "data.hpp"

TEST(Detector, setInputSize) {
  Detector detector;
  cv::Size s(100.0, 100.0);
  ASSERT_NO_THROW(detector.setInputSize(s));
}

TEST(Detector, setScoreThreshold) {
  Detector detector;
  double score_thresh = 0.2;
  ASSERT_NO_THROW(detector.setScoreThreshold(score_thresh));
}

TEST(Detector, setConfidenceThreshold) {
  Detector detector;
  double conf_thresh = 0.2;
  ASSERT_NO_THROW(detector.setConfidenceThreshold(conf_thresh));
}

TEST(Detector, setNMSThreshold) {
  Detector detector;
  double val = 0.2;
  ASSERT_NO_THROW(detector.setNMSThreshold(val));
}

TEST(Detector, setClassesToDetect) {
  Detector detector;
  std::vector<std::string> classes{"person", "car"};
  ASSERT_NO_THROW(detector.setClassesToDetect(classes));
}

TEST(Detector, setModelPath1) {
  Detector detector;
  ASSERT_NO_THROW(detector.setModelPath("./../data/models/YOLOv5s.onnx"));
}

TEST(Detector, setModelPath2) {
  Detector detector;
  ASSERT_ANY_THROW(detector.setModelPath("./../"));
}

TEST(Detector, setClassList) {
  Detector detector;
  ASSERT_NO_THROW(detector.setClassList("./../"));
}

TEST(Preprocessor, preProcess1) {
  Preprocessor preprocessor;
  cv::Mat img;
  ASSERT_ANY_THROW(preprocessor.preProcess(img));
}

TEST(Preprocessor, preProcess2) {
  Preprocessor preprocessor;
  cv::Mat img = cv::imread("./../data/test/1.jpg");
  ASSERT_NO_THROW(preprocessor.preProcess(img));
}

TEST(Preprocessor, getInputSize1) {
  Preprocessor preprocessor;
  ASSERT_NO_THROW(preprocessor.getInputSize());
}

TEST(Data, Init1) {
  std::string mode = "images";
  ASSERT_NO_THROW(Data data(mode, mode, mode));
}

TEST(Data, getInput1) {
  std::string mode = "images";
  Data data(mode, mode, mode);
  ASSERT_NO_THROW(data.getInput());
}

TEST(Data, getInput2) {
  std::string mode = "images";
  Data data(mode, mode, mode);
  cv::Mat img = data.getInput();
  ASSERT_NE(img.size().height, 100);
}

TEST(Data, getInput3) {
  std::string mode = "stream";
  Data data(mode, mode, mode);
  cv::Mat img = data.getInput();
  ASSERT_NE(img.size().height, 100);
}

TEST(Data, writeData1) {
  std::string s = "images";
  Data data(s, s, s);
  ASSERT_ANY_THROW(data.writeData(cv::Mat(), s));
}

TEST(Data, writeData2) {
  std::string s = "images";
  Data data(s, s, s);
  cv::Mat img(320, 240, CV_8UC3, cv::Scalar(0, 0, 0));
  ASSERT_NO_THROW(data.writeData(img, s));
}