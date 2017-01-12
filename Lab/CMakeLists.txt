cmake_minimum_required(VERSION 3.6)
project(CS11)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Lab3/Point.cc Lab3/Point.hh Lab3/tsp-ga.cc Lab3/tsp-ga.h Lab3/tsp-main.cc)
add_executable(CS11 ${SOURCE_FILES})