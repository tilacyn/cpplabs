cmake_minimum_required(VERSION 3.5)
project(hw_03)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/huffman.cpp include/huffman.h test/autotest.cpp test/autotest.h test/huffman_test.cpp test/huffman_test.h test/test.cpp)
add_executable(hw_03 ${SOURCE_FILES})