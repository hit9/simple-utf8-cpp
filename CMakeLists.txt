cmake_minimum_required(VERSION 3.10)

project(
  simple_utf8
  VERSION 1.0.2
  DESCRIPTION
    "Tiny simple library to convert between utf8 bytes and char32_t codepoints in C++."
)

option(SIMPLE_UTF8_TEST "Enables testing and builds tests" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INSTALL_INCLUDEDIR include)

add_library(simple_utf8 SHARED simple_utf8.cc)
set_target_properties(simple_utf8 PROPERTIES PUBLIC_HEADER "simple_utf8.h")

if(SIMPLE_UTF8_TEST)
  add_subdirectory(tests EXCLUDE_FROM_ALL)
  add_subdirectory(example EXCLUDE_FROM_ALL)
endif()

install(
  TARGETS simple_utf8
  LIBRARY DESTINATION ${CMAK_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
