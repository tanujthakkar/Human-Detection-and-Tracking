#ifndef INCLUDE_ACME_PERCEPTION_HPP
#define INCLUDE_ACME_PERCEPTION_HPP

#include <data.hpp>
#include <detector.hpp>
#include <preprocessor.hpp>

class AcmePerception {
 public:
  AcmePerception(std::string& mode, std::string& input_path,
                 std::string& output_path);

  ~AcmePerception();

  void processInputs();

 private:
  Detector detector_;

  Preprocessor preprocessor_;

  Data data_;
};

#endif