#include <catch2/catch_test_macros.hpp>
#include <string>

#include "simple_utf8.h"
#include "util.h"

using namespace simple_utf8_test_util;

// https://www.cl.cam.ac.uk/~mgk25/ucs/examples/UTF-8-demo.txt
TEST_CASE("Decode", "[Decode file data #1]") {
  auto s = ReadFile("data/UTF-8-demo.txt");
  auto target = ReadCodepointsFromFile("data/UTF-8-demo-codepoints.txt");
  REQUIRE(s.size() > 0);
  REQUIRE(target.size() > 0);
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::Decode(s, p) > 0);
  REQUIRE(p == target);
}

// https://www.cl.cam.ac.uk/~mgk25/ucs/examples/UTF-8-demo.txt
TEST_CASE("DecodeNaive", "[DecodeNaive file data #1]") {
  auto s = ReadFile("data/UTF-8-demo.txt");
  auto target = ReadCodepointsFromFile("data/UTF-8-demo-codepoints.txt");
  REQUIRE(s.size() > 0);
  REQUIRE(target.size() > 0);
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::DecodeNaive(s, p) > 0);
  REQUIRE(p == target);
}

TEST_CASE("Decode", "[Decode file data #2]") {
  auto s = ReadFile("data/UTF-8-cn.txt");
  auto target = ReadCodepointsFromFile("data/UTF-8-cn-codepoints.txt");
  REQUIRE(s.size() > 0);
  REQUIRE(target.size() > 0);
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::Decode(s, p) > 0);
  REQUIRE(p == target);
}

TEST_CASE("DecodeNaive", "[DecodeNaive file data #2]") {
  auto s = ReadFile("data/UTF-8-cn.txt");
  auto target = ReadCodepointsFromFile("data/UTF-8-cn-codepoints.txt");
  REQUIRE(s.size() > 0);
  REQUIRE(target.size() > 0);
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::DecodeNaive(s, p) > 0);
  REQUIRE(p == target);
}

TEST_CASE("Decode", "[Decode file data #3]") {
  auto s = ReadFile("data/UTF-8-random-1.txt");
  auto target =
      ReadCodepointsFromFile("data/UTF-8-random-1-codepoints.txt");
  REQUIRE(s.size() > 0);
  REQUIRE(target.size() > 0);
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::Decode(s, p) > 0);
  REQUIRE(p == target);
}

TEST_CASE("DecodeNaive", "[DecodeNaive file data #3]") {
  auto s = ReadFile("data/UTF-8-random-1.txt");
  auto target =
      ReadCodepointsFromFile("data/UTF-8-random-1-codepoints.txt");
  REQUIRE(s.size() > 0);
  REQUIRE(target.size() > 0);
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::DecodeNaive(s, p) > 0);
  REQUIRE(p == target);
}

TEST_CASE("Decode", "[Decode file data #4]") {
  auto s = ReadFile("data/UTF-8-en.txt");
  auto target = ReadCodepointsFromFile("data/UTF-8-en-codepoints.txt");
  REQUIRE(s.size() > 0);
  REQUIRE(target.size() > 0);
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::Decode(s, p) > 0);
  REQUIRE(p == target);
}

TEST_CASE("DecodeNaive", "[DecodeNaive file data #4]") {
  auto s = ReadFile("data/UTF-8-en.txt");
  auto target = ReadCodepointsFromFile("data/UTF-8-en-codepoints.txt");
  REQUIRE(s.size() > 0);
  REQUIRE(target.size() > 0);
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::DecodeNaive(s, p) > 0);
  REQUIRE(p == target);
}
