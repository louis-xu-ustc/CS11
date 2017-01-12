cmake_minimum_required(VERSION 3.6)
project(Lab1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES lab1.cc Point.cc Point.hh)
add_executable(Lab1 ${SOURCE_FILES})