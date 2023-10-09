#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include <string>

#include "simple_utf8.h"

static std::u32string ReadCodepointsFromFile(std::string_view filename) {
  // read file
  std::string s;
  std::getline(std::ifstream(filename), s, '\0');
  // parse codepoint split by ', '
  std::u32string codepoints;
  std::string tmp;
  char32_t codepoint;

  auto push = [&]() {
    codepoint = static_cast<char32_t>(std::stol(tmp));
    codepoints.push_back(codepoint);
  };

  for (auto b : s) {
    switch (b) {
      case ',':
        push();
        tmp.clear();
        break;
      case ' ':  // ignore whitespaces
        break;
      default:
        tmp.push_back(b);
        break;
    }
  }

  // trailling codepoint.
  if (!tmp.empty()) push();
  return codepoints;
}

// https://www.cl.cam.ac.uk/~mgk25/ucs/examples/UTF-8-demo.txt
TEST_CASE("Decode", "[Decode file data #1]") {
  // read file
  std::string s;
  std::getline(std::ifstream("tests/data/UTF-8-demo.txt"), s, '\0');
  auto target = ReadCodepointsFromFile("tests/data/UTF-8-demo-codepoints.txt");
  REQUIRE(s.size() > 0);
  REQUIRE(target.size() > 0);
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::Decode(s, p) > 0);
  REQUIRE(p == target);
}

// https://www.cl.cam.ac.uk/~mgk25/ucs/examples/UTF-8-demo.txt
TEST_CASE("DecodeNaive", "[DecodeNaive file data #1]") {
  // read file
  std::string s;
  std::getline(std::ifstream("tests/data/UTF-8-demo.txt"), s, '\0');
  auto target = ReadCodepointsFromFile("tests/data/UTF-8-demo-codepoints.txt");
  REQUIRE(s.size() > 0);
  REQUIRE(target.size() > 0);
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::DecodeNaive(s, p) > 0);
  REQUIRE(p == target);
}
