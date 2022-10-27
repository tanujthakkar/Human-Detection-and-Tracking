include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/app
)

set(app_src
    data.cpp
    detector.cpp
    preprocessor.cpp
    acme_perception.cpp

    main.cpp)

add_library(app_lib ${app_src})
add_executable(acme_perception main.cpp)
target_link_libraries(acme_perception
    app_lib
    ${OpenCV_LIBS})