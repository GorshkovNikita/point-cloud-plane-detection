cmake_minimum_required(VERSION 3.14)
project(point_cloud_plane_detection)

set(CMAKE_CXX_STANDARD 11)

configure_file(simple_point_cloud_test.txt input.txt COPYONLY)

add_executable(point_cloud_plane_detection main.cpp)