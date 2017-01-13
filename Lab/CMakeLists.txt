cmake_minimum_required(VERSION 3.6)
project(CS11)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Lab4/maze.cc Lab4/maze.hh)
add_executable(CS11 ${SOURCE_FILES})