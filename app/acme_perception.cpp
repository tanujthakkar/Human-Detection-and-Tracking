#include <acme_perception.hpp>

AcmePerception::AcmePerception(std::string& mode, std::string& input_path,
                               std::string& output_path) {
  data_.setInputMode(mode);
  data_.setIOpaths(input_path, output_path);

  detector_.setInputSize(cv::Size(640, 640));
  detector_.setScoreThreshold(0.5);
  detector_.setConfidenceThreshold(0.45);
  detector_.setNMSThreshold(0.5);
  std::vector<std::string> classes{"person", "car"};
  detector_.setClassesToDetect(classes);
  detector_.setModelPath("./../data/models/YOLOv5s.onnx");
  detector_.setClassList("./../data/models/coco.names");
}

AcmePerception::~AcmePerception() {}

void AcmePerception::processInputs() {
  cv::Mat img, output;
  bool save_output = false;
  int counter = 0;
  while (cv::waitKey(1) != 27) {
    img = data_.getInput();
    if (img.empty()) {
      std::cout << "empty image found, exiting";
      break;
    }
    cv::Mat blob = preprocessor_.preProcess(img);
    output = detector_.detect(blob, img);

    cv::imshow("output", output);
    cv::waitKey(0);
    if (save_output) {
      data_.writeData(output, std::to_string(counter));
      counter += 1;
    }
  }
}