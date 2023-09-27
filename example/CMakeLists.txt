cmake_minimum_required(VERSION 3.10)
project(simple_utf8_example CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("..")

# Targets
add_executable(example main.cc ../simple_utf8.cc)
target_link_libraries(example)
