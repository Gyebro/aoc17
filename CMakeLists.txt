cmake_minimum_required(VERSION 3.8)
project(aoc17)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        src/main.cpp src/common.cpp src/common.h)

add_executable(aoc17 ${SOURCE_FILES})

# Copy contents of 'input' to build directory
add_custom_command(TARGET aoc17 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/input"
        $<TARGET_FILE_DIR:aoc17>)