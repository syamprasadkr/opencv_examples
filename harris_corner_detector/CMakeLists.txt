cmake_minimum_required(VERSION 2.8)
project(harris_corner_detector)
set(CMAKE_CXX_STANDARD 11)
find_package(OpenCV REQUIRED)
set(SOURCES harris_corner_detector.cpp)
add_executable(harris_corner_detector ${SOURCES})
target_link_libraries(harris_corner_detector ${OpenCV_LIBS})
