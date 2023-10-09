cmake_minimum_required(VERSION 3.10)
project(simple_utf8_tests CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("..")

# Find or Download package Catch 2
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0 # or a later release
    GIT_PROGRESS TRUE
    FIND_PACKAGE_ARGS NAMES Catch2)

FetchContent_MakeAvailable(Catch2)

# Targets
file(GLOB TEST_SOURCES *_test.cc)
add_executable(tests ${TEST_SOURCES} util.cc ../simple_utf8.cc)
add_executable(benchmark benchmark.cc util.cc ../simple_utf8.cc)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(benchmark PRIVATE Catch2::Catch2WithMain)
