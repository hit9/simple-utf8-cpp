#include <iostream>
#include <string>
#include "simple_utf8.h"

int main() {
  // Decoding via DFA
  std::string s("你好世界, hello world! 😊");
  std::u32string p(simple_utf8::CountCodes(s), 0);
  auto n = simple_utf8::Decode(s, p);  // returns number of codepoints.
  for (auto codepoint : p) std::cout << codepoint << std::endl;

  // Decoding via naive approach.
  std::u32string p1(simple_utf8::CountCodes(s), 0);
  auto n1 = simple_utf8::DecodeNaive(s, p1);
  for (auto codepoint : p1) std::cout << codepoint << std::endl;

  // Encoding
  std::string s2(simple_utf8::CountBytes(p), 0);
  auto k = simple_utf8::Encode(p, s2);
  std::cout << s2 << std::endl;
  return 0;
}
