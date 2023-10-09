#ifndef HIT9_SIMPLE_UTF8_TEST_UTIL_H_
#define HIT9_SIMPLE_UTF8_TEST_UTIL_H_

#include <string>

namespace simple_utf8_test_util {

std::u32string ReadCodepointsFromFile(std::string_view filename);
std::string ReadFile(std::string_view filename);

}

#endif  // HIT9_SIMPLE_UTF8_TEST_UTIL_H_
