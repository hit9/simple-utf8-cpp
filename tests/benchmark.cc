#include <catch2/benchmark/catch_benchmark_all.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string>

#include "simple_utf8.h"
#include "util.h"

using namespace simple_utf8_test_util;

// {{{ Decoding Benchmark

TEST_CASE("Decoding Benchmark", "[Decode benchmark #1]") {
  auto s = ReadFile("tests/data/UTF-8-demo.txt");
  auto target = ReadCodepointsFromFile("tests/data/UTF-8-demo-codepoints.txt");
  REQUIRE(s.size() > 0);
  REQUIRE(target.size() > 0);
  std::u32string p(simple_utf8::CountCodes(s), 0);

  // Benchmark
  BENCHMARK("Decode benchmark (UTF-8-demo.txt)") {
    return simple_utf8::Decode(s, p);
  };
  BENCHMARK("DecodeNaive benchmark (UTF-8-demo.txt)") {
    return simple_utf8::DecodeNaive(s, p);
  };
}

TEST_CASE("Decoding Benchmark", "[Decode benchmark #2]") {
  auto s = ReadFile("tests/data/UTF-8-cn.txt");
  auto target = ReadCodepointsFromFile("tests/data/UTF-8-cn-codepoints.txt");
  REQUIRE(s.size() > 0);
  REQUIRE(target.size() > 0);
  std::u32string p(simple_utf8::CountCodes(s), 0);

  // Benchmark
  BENCHMARK("Decode benchmark (chinese)") { return simple_utf8::Decode(s, p); };
  BENCHMARK("DecodeNaive benchmark (chinese)") {
    return simple_utf8::DecodeNaive(s, p);
  };
}

TEST_CASE("Decoding Benchmark", "[Decode benchmark #3]") {
  auto s = ReadFile("tests/data/UTF-8-random-1.txt");
  auto target =
      ReadCodepointsFromFile("tests/data/UTF-8-random-1-codepoints.txt");
  REQUIRE(s.size() > 0);
  REQUIRE(target.size() > 0);
  std::u32string p(simple_utf8::CountCodes(s), 0);

  // Benchmark
  BENCHMARK("Decode benchmark (random)") { return simple_utf8::Decode(s, p); };
  BENCHMARK("DecodeNaive benchmark (random)") {
    return simple_utf8::DecodeNaive(s, p);
  };
}

TEST_CASE("Decoding Benchmark", "[Decode benchmark #4]") {
  auto s = ReadFile("tests/data/UTF-8-en.txt");
  auto target = ReadCodepointsFromFile("tests/data/UTF-8-en-codepoints.txt");
  REQUIRE(s.size() > 0);
  REQUIRE(target.size() > 0);
  std::u32string p(simple_utf8::CountCodes(s), 0);

  // Benchmark
  BENCHMARK("Decode benchmark (english)") { return simple_utf8::Decode(s, p); };
  BENCHMARK("DecodeNaive benchmark (english)") {
    return simple_utf8::DecodeNaive(s, p);
  };
}

// }}}
