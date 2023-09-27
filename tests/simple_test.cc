#include <catch2/catch_test_macros.hpp>
#include <string>

#include "simple_utf8.h"

TEST_CASE("CountCodes", "[Count codepoints simple #1]") {
  std::string s("§©Abcµ火eng\n");
  REQUIRE(simple_utf8::CountCodes(s) == 11);
}

TEST_CASE("CountCodes", "[Count codepoints simple #2]") {
  std::string s("ÂAÕO五6!~");
  REQUIRE(simple_utf8::CountCodes(s) == 8);
}

TEST_CASE("CountBytes", "[Count bytes simple #1]") {
  std::u32string p({194, 65, 213, 79, 20116, 54, 33, 126});
  REQUIRE(simple_utf8::CountBytes(p) == 12);
}

TEST_CASE("Decode", "[Decode simple #1]") {
  std::string s("english and 中文混合");
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::Decode(s, p) == 16);
  std::u32string target({101, 110, 103, 108, 105, 115, 104, 32, 97, 110, 100,
                         32, 20013, 25991, 28151, 21512});
  REQUIRE(p == target);
}

TEST_CASE("Encode", "[Encode simple #1]") {
  std::string s1("english and 中文混合");
  std::u32string p({101, 110, 103, 108, 105, 115, 104, 32, 97, 110, 100, 32,
                    20013, 25991, 28151, 21512});
  std::string s(4 * p.size(), 0);
  auto k = simple_utf8::Encode(p, s);
  s.resize(k);
  REQUIRE(s == s1);
}
TEST_CASE("Encode", "[Encode simple #2]") {
  std::string s1("english and 中文混合");
  std::u32string p({101, 110, 103, 108, 105, 115, 104, 32, 97, 110, 100, 32,
                    20013, 25991, 28151, 21512});
  std::string s(simple_utf8::CountBytes(p), 0);
  auto k = simple_utf8::Encode(p, s);
  REQUIRE(k == s.size());
  REQUIRE(s == s1);
}
