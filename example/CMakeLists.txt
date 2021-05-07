cmake_minimum_required(VERSION 3.0)
project(goldtest)

set(CMAKE_CXX_STANDARD 20)
find_package(GTest REQUIRED 1.8.0)
include_directories(${GTEST_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/../goldtest ${CMAKE_SOURCE_DIR}/dtl)

# goldtest target ======================================================================================================
add_executable(goldtest main.cpp src/file_writer.hpp src/file_writer.cpp src/tests/file_writer_test.cpp)
target_link_libraries(goldtest ${GTEST_BOTH_LIBRARIES})

# Target for copying .gold files =======================================================================================
add_custom_target(copy_gold_files ALL)

# Make a directory called test_data/ in build directory
add_custom_command(TARGET copy_gold_files PRE_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory test_data)

# Recursively look through our source files for .gold files and copy them to that directory
file(GLOB_RECURSE gold_files "*.gold")
foreach(test_file ${gold_files})
    get_filename_component(file_name ${test_file} NAME)
    add_custom_command(
            TARGET copy_gold_files PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${test_file}
            ${CMAKE_CURRENT_BINARY_DIR}/test_data/${file_name})
endforeach()
add_dependencies(goldtest copy_gold_files)