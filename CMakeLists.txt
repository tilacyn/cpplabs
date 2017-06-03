#cmake_minimum_required(VERSION 3.5)
#project(test1)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Werror -std=c++11 -pedantic -Wextra -lgtest_main -lgtest -lpthread")

#set(SOURCE_FILES test/test1.cpp test/autotest.h test/autotest.cpp test/huffman_test.cpp test/huffman_test.h src/huffman.cpp)
#set(SOURCE_FILES new_test.cpp)
#add_executable(test1 ${SOURCE_FILES})

cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(../include/)
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(test test.cpp ../src/huffman.cpp)
target_link_libraries(test ${GTEST_LIBRARIES} pthread)
