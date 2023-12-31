// Copyright 2023, Chao Wang <hit9@icloud.com>
// Tiny simple library to convert between utf8 bytes and char32_t codepoints in
// C++.

#ifndef HIT9_SIMPLE_UTF8_H_
#define HIT9_SIMPLE_UTF8_H_

#include <cstddef>      // for std::size_t
#include <string>       // for std::string, std::u32string
#include <string_view>  // for std::string_view, std::u32string_view

namespace simple_utf8 {

using size_t = std::size_t;

// Count codepoints in given utf8 string.
size_t CountCodes(std::string_view s);

// Count bytes for given codepoint sequence.
size_t CountBytes(std::u32string_view p);

// Decode utf8 string to codepoint buffer via Bjoern Hoehrmann DFA approach.
// Returns number of codepoints decoded.
// Returns 0 if given utf8 string is invalid.
size_t Decode(std::string_view s, std::u32string &p);

// Decode utf8 string to codepoint buffer via naive traditional approach.
// Returns number of codepoints decoded.
// Returns 0 if given utf8 string is invalid.
size_t DecodeNaive(std::string_view s, std::u32string &p);

// Encode codepoint buffer to utf8 string.
// Returns number of chars encoded.
// Returns 0 if given codepoint buffer is invalid.
size_t Encode(std::u32string_view, std::string &s);

}  // namespace simple_utf8
#endif  // HIT9_SIMPLE_UTF8_H_
