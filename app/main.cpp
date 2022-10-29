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
 * @file detector.cpp
 * @author Nitesh Jha (Driver), Tanuj Thakkar (Navigator)
 * @brief Detection class definition for AcmePerception
 * @version 0.1
 * @date 2022-10-19
 *
 *
 */

#include <acme_perception.hpp>

int main(int argc, char** argv) {
  if (argc != 5) {
    std::cout
        << "\n Usage: ./acme_perception [mode] [input_path] [output_path] "
           "[save_data]\nInvalid number of arguments. returning..."
        << std::endl;
    return 0;
  }

  Acme::AcmePerception acme(argv[1], argv[2], argv[3], argv[4]);
  acme.processInputs(true);
  return 0;
}
