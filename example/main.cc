#include <iostream>
#include <string>

#include "simple_utf8.h"

int main() {
  // Decoding
  std::string s("你好世界, hello world! 😊");
  std::u32string p(simple_utf8::CountCodes(s), 0);
  auto n = simple_utf8::Decode(s, p);  // returns number of codepoints.
  for (auto codepoint : p) std::cout << codepoint << std::endl;

  // Encoding
  std::string s1(simple_utf8::CountBytes(p), 0);
  auto k = simple_utf8::Encode(p, s1);
  std::cout << s1 << std::endl;
  return 0;
}
