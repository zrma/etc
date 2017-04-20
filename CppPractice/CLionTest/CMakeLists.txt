cmake_minimum_required(VERSION 3.6)
project(CLionTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(CLionTest ${SOURCE_FILES})