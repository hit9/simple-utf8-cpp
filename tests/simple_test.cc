#include <catch2/catch_test_macros.hpp>
#include <string>

#include "simple_utf8.h"

// {{{ Count

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

// Count }}}

/// {{{ Decode
TEST_CASE("Decode", "[Decode simple #1]") {
  std::string s("english and 中文混合");
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::Decode(s, p) == 16);
  std::u32string target({101, 110, 103, 108, 105, 115, 104, 32, 97, 110, 100,
                         32, 20013, 25991, 28151, 21512});
  REQUIRE(p == target);
}

TEST_CASE("Decode", "[Decode simple #2]") {
  std::string s("🐣🦋|↑|。!x");
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::Decode(s, p) == 8);
  std::u32string target({128035, 129419, 124, 8593, 124, 12290, 33, 120});
  REQUIRE(p == target);
}

TEST_CASE("Decode", "[Decode simple #3]") {
  std::string s("世界你好ヽ(￣▽￣)و👌の");
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::Decode(s, p) == 13);
  std::u32string target({19990, 30028, 20320, 22909, 12541, 40, 65507, 9661,
                         65507, 41, 1608, 128076, 12398});
  REQUIRE(p == target);
}

TEST_CASE("Decode", "[Decode invalid #1]") {
  unsigned char x[4] = {0xF0, 0x80, 0x80, 0x8A};
  std::string s(reinterpret_cast<char*>(x), 4);
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::Decode(s, p) == 0);
}

TEST_CASE("Decode", "[Decode invalid #2]") {
  unsigned char x[2] = {0xC1, 0x80};
  std::string s(reinterpret_cast<char*>(x), 2);
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::Decode(s, p) == 0);
}

TEST_CASE("Decode", "[Decode invalid #3]") {
  unsigned char x[4] = {0xF4, 0x90, 0x80, 0x80};
  std::string s(reinterpret_cast<char*>(x), 4);
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::Decode(s, p) == 0);
}

TEST_CASE("Decode", "[Decode invalid #4]") {
  unsigned char x[6] = {0xFC, 0x80, 0x80, 0x80, 0x80, 0x8A};
  std::string s(reinterpret_cast<char*>(x), 6);
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::Decode(s, p) == 0);
}

TEST_CASE("DecodeNaive", "[DecodeNaive simple #1]") {
  std::string s("english and 中文混合");
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::DecodeNaive(s, p) == 16);
  std::u32string target({101, 110, 103, 108, 105, 115, 104, 32, 97, 110, 100,
                         32, 20013, 25991, 28151, 21512});
  REQUIRE(p == target);
}

TEST_CASE("DecodeNaive", "[DecodeNaive simple #2]") {
  std::string s("🐣🦋|↑|。!x");
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::DecodeNaive(s, p) == 8);
  std::u32string target({128035, 129419, 124, 8593, 124, 12290, 33, 120});
  REQUIRE(p == target);
}

TEST_CASE("DecodeNaive", "[DecodeNaive simple #3]") {
  std::string s("世界你好ヽ(￣▽￣)و👌の");
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::DecodeNaive(s, p) == 13);
  std::u32string target({19990, 30028, 20320, 22909, 12541, 40, 65507, 9661,
                         65507, 41, 1608, 128076, 12398});
  REQUIRE(p == target);
}

TEST_CASE("DecodeNaive", "[DecodeNaive simple #4]") {
  std::string s(
      "Σὲ γνωρίζω ἀπὸ τὴν κόψη τοῦ σπαθιοῦ τὴν τρομερή, σὲ γνωρίζω ἀπὸ τὴν ὄψη "
      "ποὺ μὲ βία μετράει τὴ γῆ.");
  std::u32string target(
      {931,  8050, 32,  947,  957,  969, 961, 943, 950,  969,  32,   7936, 960,
       8056, 32,   964, 8052, 957,  32,  954, 972, 968,  951,  32,   964,  959,
       8166, 32,   963, 960,  945,  952, 953, 959, 8166, 32,   964,  8052, 957,
       32,   964,  961, 959,  956,  949, 961, 942, 44,   32,   963,  8050, 32,
       947,  957,  969, 961,  943,  950, 969, 32,  7936, 960,  8056, 32,   964,
       8052, 957,  32,  8004, 968,  951, 32,  960, 959,  8058, 32,   956,  8050,
       32,   946,  943, 945,  32,   956, 949, 964, 961,  940,  949,  953,  32,
       964,  8052, 32,  947,  8134, 46});
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::DecodeNaive(s, p) == 97);
  REQUIRE(p == target);
}

TEST_CASE("Decode", "[Decode simple #4]") {
  std::string s(
      "Σὲ γνωρίζω ἀπὸ τὴν κόψη τοῦ σπαθιοῦ τὴν τρομερή, σὲ γνωρίζω ἀπὸ τὴν ὄψη "
      "ποὺ μὲ βία μετράει τὴ γῆ.");
  std::u32string target(
      {931,  8050, 32,  947,  957,  969, 961, 943, 950,  969,  32,   7936, 960,
       8056, 32,   964, 8052, 957,  32,  954, 972, 968,  951,  32,   964,  959,
       8166, 32,   963, 960,  945,  952, 953, 959, 8166, 32,   964,  8052, 957,
       32,   964,  961, 959,  956,  949, 961, 942, 44,   32,   963,  8050, 32,
       947,  957,  969, 961,  943,  950, 969, 32,  7936, 960,  8056, 32,   964,
       8052, 957,  32,  8004, 968,  951, 32,  960, 959,  8058, 32,   956,  8050,
       32,   946,  943, 945,  32,   956, 949, 964, 961,  940,  949,  953,  32,
       964,  8052, 32,  947,  8134, 46});
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::Decode(s, p) == 97);
  REQUIRE(p == target);
}

TEST_CASE("DecodeNaive", "[DecodeNaive invalid #1]") {
  unsigned char x[4] = {0xF0, 0x80, 0x80, 0x8A};
  std::string s(reinterpret_cast<char*>(x), 4);
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::DecodeNaive(s, p) == 0);
}

TEST_CASE("DecodeNaive", "[DecodeNaive invalid #2]") {
  unsigned char x[2] = {0xC1, 0x80};
  std::string s(reinterpret_cast<char*>(x), 2);
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::DecodeNaive(s, p) == 0);
}

TEST_CASE("DecodeNaive", "[DecodeNaive invalid #3]") {
  unsigned char x[4] = {0xF4, 0x90, 0x80, 0x80};
  std::string s(reinterpret_cast<char*>(x), 4);
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::DecodeNaive(s, p) == 0);
}

TEST_CASE("DecodeNaive", "[DecodeNaive invalid #4]") {
  unsigned char x[6] = {0xFC, 0x80, 0x80, 0x80, 0x80, 0x8A};
  std::string s(reinterpret_cast<char*>(x), 6);
  std::u32string p(simple_utf8::CountCodes(s), 0);
  REQUIRE(simple_utf8::DecodeNaive(s, p) == 0);
}

/// Decode }}}

/// {{{ Encode
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

TEST_CASE("Encode", "[Encode simple #3]") {
  std::string s1("Ɔ⭐️❤123Ẹ⎰");
  std::u32string p({390, 11088, 65039, 10084, 49, 50, 51, 7864, 9136});
  std::string s(simple_utf8::CountBytes(p), 0);
  auto k = simple_utf8::Encode(p, s);
  REQUIRE(k == s.size());
  REQUIRE(s == s1);
}

TEST_CASE("Encode", "[Encode simple #4]") {
  std::string s1("世界你好ヽ(￣▽￣)و👌の");
  std::u32string p({19990, 30028, 20320, 22909, 12541, 40, 65507, 9661, 65507,
                    41, 1608, 128076, 12398});
  std::string s(simple_utf8::CountBytes(p), 0);
  auto k = simple_utf8::Encode(p, s);
  REQUIRE(k == s.size());
  REQUIRE(s == s1);
}

/// Encode }}}
