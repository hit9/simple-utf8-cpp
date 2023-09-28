cmake_minimum_required(VERSION 3.10)

project(
  simple_utf8
  VERSION 1.0.0
  DESCRIPTION
    "Tiny simple library to convert between utf8 bytes and char32_t codepoints in C++."
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INSTALL_INCLUDEDIR include)

add_library(simple_utf8 SHARED simple_utf8.cc)

install(TARGETS simple_utf8 LIBRARY DESTINATION ${CMAK_INSTALL_LIBDIR})
install(FILES simple_utf8.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
