cmake_minimum_required(VERSION 2.8)
project(edge_detectors)
set(CMAKE_CXX_STANDARD 11)
find_package(OpenCV REQUIRED)
set(SOURCES edge_detectors.cpp)
add_executable(edge_detectors ${SOURCES})
target_link_libraries(edge_detectors ${OpenCV_LIBS})
