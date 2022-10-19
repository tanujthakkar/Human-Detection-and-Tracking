#include <fstream>
#include <opencv2/dnn/dnn.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include "detector.hpp"
#include "data.hpp"
#include "preprocessor.hpp"
#include "acme_perception.hpp"


int main(int argc, char **argv) {

  std::string mode = "images";
  std::string input= "./../data/test/";
  std::string output= "./../data/test/test_output";

  AcmePerception acme(mode, input, output);
  acme.processInputs();
  return 0;
}
