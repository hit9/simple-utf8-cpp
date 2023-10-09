#ifndef HIT9_SIMPLE_UTF8_TEST_UTIL_H_
#define HIT9_SIMPLE_UTF8_TEST_UTIL_H_

#include <string>

namespace simple_utf8_test_util {

std::u32string ReadCodepointsFromFile(const std::string& filename);
std::string ReadFile(const std::string& filename);

}  // namespace simple_utf8_test_util

#endif  // HIT9_SIMPLE_UTF8_TEST_UTIL_H_
