#include <fstream>
#include <string>

namespace simple_utf8_test_util {

std::u32string ReadCodepointsFromFile(std::string_view filename) {
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

std::string ReadFile(std::string_view filename) {
  std::string s;
  std::getline(std::ifstream(filename), s, '\0');
  return s;
}

}  // namespace simple_utf8_test_util
