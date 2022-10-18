#include <fstream>
#include <opencv2/dnn/dnn.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include "detector.hpp"

int main(int argc, char **argv) {
  Detector detector;

  detector.logDetectorInfo();

  cv::Mat frame;
  frame = cv::imread("./../data/traffic.jpg");
  cv::Mat output = detector.detect(frame);
  cv::imshow("final output", output);
  cv::waitKey(0);

  frame = cv::imread("./../data/1.jpg");
  output = detector.detect(frame);
  cv::imshow("final output", output);
  cv::waitKey(0);

  frame = cv::imread("./../data/car.jpg");
  output = detector.detect(frame);
  cv::imshow("final output", output);
  cv::waitKey(0);

  return 0;
}
