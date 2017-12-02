include(ExternalProject)

# GoogleTest external project
externalproject_add(gtest-download
        PREFIX gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.7.0
        INSTALL_COMMAND   ""
        )
add_library(gtest STATIC IMPORTED GLOBAL)
add_library(gtest-main STATIC IMPORTED GLOBAL)
set_target_properties(gtest PROPERTIES IMPORTED_LOCATION
        ${PROJECT_BINARY_DIR}/tests/gtest/src/gtest-download-build/libgtest.a)
set_target_properties(gtest-main PROPERTIES IMPORTED_LOCATION
        ${PROJECT_BINARY_DIR}/tests/gtest/src/gtest-download-build/libgtest_main.a)

# AoC17 Tests
set(SOURCE_FILES
        tests.cpp)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_BINARY_DIR}/tests/gtest/src/gtest-download/include)
add_executable(aoc17-tests ${SOURCE_FILES})
add_dependencies(aoc17-tests gtest-download)
target_link_libraries(aoc17-tests gtest gtest-main pthread)