#include <catch2/catch_test_macros.hpp>
#include <string>

#include "simple_utf8.h"

TEST_CASE("Count", "[Count simple #1]") {
  std::string s("§©Abcµ火eng\n");
  REQUIRE(simple_utf8::Count(s) == 11);
}

TEST_CASE("Count", "[Count simple #2]") {
  std::string s("ÂAÕO五6!~");
  REQUIRE(simple_utf8::Count(s) == 8);
}

TEST_CASE("Decode", "[Decode simple #1]") {
  std::string s("english and 中文混合");
  std::u32string p(simple_utf8::Count(s), 0);
  REQUIRE(simple_utf8::Decode(s, p) == 16);
  REQUIRE(p[0] == 101);
  REQUIRE(p[1] == 110);
  REQUIRE(p[2] == 103);
  REQUIRE(p[3] == 108);
  REQUIRE(p[4] == 105);
  REQUIRE(p[5] == 115);
  REQUIRE(p[6] == 104);
  REQUIRE(p[7] == 32);
  REQUIRE(p[8] == 97);
  REQUIRE(p[9] == 110);
  REQUIRE(p[10] == 100);
  REQUIRE(p[11] == 32);
  REQUIRE(p[12] == 20013);
  REQUIRE(p[13] == 25991);
  REQUIRE(p[14] == 28151);
  REQUIRE(p[15] == 21512);
}

TEST_CASE("Encode", "[Encode simple #1]") {
  std::string s1("english and 中文混合");
  std::u32string p;
  p.push_back(101);
  p.push_back(110);
  p.push_back(103);
  p.push_back(108);
  p.push_back(105);
  p.push_back(115);
  p.push_back(104);
  p.push_back(32);
  p.push_back(97);
  p.push_back(110);
  p.push_back(100);
  p.push_back(32);
  p.push_back(20013);
  p.push_back(25991);
  p.push_back(28151);
  p.push_back(21512);
  std::string s(4 * p.size(), 0);
  auto k = simple_utf8::Encode(p, s);
  s.resize(k);
  REQUIRE(s == s1);
}
