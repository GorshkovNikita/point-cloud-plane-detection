cmake_minimum_required(VERSION 3.14)
project(point_cloud_plane_detection)

set(CMAKE_CXX_STANDARD 17)

configure_file(sdc_point_cloud.txt input.txt COPYONLY)

add_executable(point_cloud_plane_detection main.cpp)