#include <gtest/gtest.h>
#include "detector.hpp"

TEST(Detector, setInputSize) {
  Detector detector;
  cv::Size s(100.0,100.0);
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
  std::vector<std::string> classes{"person","car"};
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
