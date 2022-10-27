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
 * @file test.hpp
 * @author Nitesh Jha (Driver), Tanuj Thakkar (Navigator)
 * @brief unit tests for API
 * @version 0.1
 * @date 2022-10-19
 *
 *
 */

#include <gtest/gtest.h>

#include <data.hpp>
#include <detector.hpp>
#include <preprocessor.hpp>

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

TEST(Detector, detect) {
  Detector detector;
  detector.setClassesToDetect({"person"});
  detector.setModelPath("./../data/models/YOLOv5s.onnx");
  detector.setClassList("./../data/models/coco.names");
  Preprocessor preprocessor;
  cv::Mat img = cv::imread("./../data/test/1.jpg");
  cv::Mat blob = preprocessor.preProcess(img);
  std::vector<std::pair<cv::Rect, float>> result = detector.detect(blob, img);
  ASSERT_EQ((int)result.size(), 1);
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
  Data data;
  data.setInputMode(mode);
  data.setIOpaths("./../data/test/", "./../data/test_output/");
  data.initialize();
  cv::Mat img = data.getInput();
  ASSERT_NE(img.size().height, 0);
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

TEST(Data, checkgetInput) {
  std::string s = "images";
  Data data(s, s, s);
  ASSERT_EQ(data.getInputMode(), s);
}
