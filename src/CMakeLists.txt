# Advent of Code 2017
set(SOURCE_FILES
        common.h
        common.cpp
        days.h
        days.cpp
        main.cpp)

add_executable(aoc17 ${SOURCE_FILES})

# Copy contents of 'input' to build directory
add_custom_command(TARGET aoc17 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/input"
        $<TARGET_FILE_DIR:aoc17>)