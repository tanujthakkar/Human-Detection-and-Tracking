include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/app
)

set(app_src
    acme_perception.cpp
    camera.cpp
    data.cpp
    detector.cpp
    preprocessor.cpp
    tracker.cpp
    transformer.cpp

    main.cpp)

add_library(app_lib ${app_src})
add_executable(acme_perception main.cpp)
target_link_libraries(acme_perception
    app_lib
    ${OpenCV_LIBS}
    ${Eigen3_LIBS})
