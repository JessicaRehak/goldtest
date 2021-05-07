cmake_minimum_required(VERSION 3.0)
project(goldtest)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED 1.8.0)
include_directories(${GTEST_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/../goldtest ${CMAKE_SOURCE_DIR}/dtl)
add_executable(goldtest main.cpp)
target_link_libraries(goldtest ${GTEST_BOTH_LIBRARIES})