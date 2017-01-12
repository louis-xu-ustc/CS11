cmake_minimum_required(VERSION 3.6)
project(CS11)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Lab2/tsp.cc Lab2/Point.cc Lab2/Point.hh)
add_executable(CS11 ${SOURCE_FILES})