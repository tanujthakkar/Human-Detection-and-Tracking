cmake_minimum_required(VERSION 3.2.1)
project (app)

# Add project cmake modules to path.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
# set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

# We probably don't want this to run on every build.
option(COVERAGE "Generate Coverage Data" OFF)

find_package(OpenCV 4.6 EXACT REQUIRED)
find_package(Eigen3 REQUIRED)

INCLUDE_DIRECTORIES(
    ${OpenCV_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIRS})

message(STATUS "OpenCV_DIR = $(OpenCV_DIR)")

if (COVERAGE)
    include(CodeCoverage)
    set(LCOV_REMOVE_EXTRA "'vendor/*' ")
    setup_target_for_coverage(code_coverage cpp-test coverage)
    # set(COVERAGE_SRCS app/main.cpp)

    SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")
else()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -g")
endif()

include(CMakeToolsHelpers OPTIONAL)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(app)
add_subdirectory(test)
add_subdirectory(vendor/googletest/googletest)