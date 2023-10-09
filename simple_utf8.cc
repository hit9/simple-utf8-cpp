#include "simple_utf8.h"

// rfc3629 https://datatracker.ietf.org/doc/html/rfc3629

// Code copy from http://bjoern.hoehrmann.de/utf-8/decoder/dfa.
// Copyright (c) 2008-2009 Bjoern Hoehrmann <bjoern@hoehrmann.de>
// See http://bjoern.hoehrmann.de/utf-8/decoder/dfa/ for details.

// clang-format off

#define UTF8_ACCEPT 0
#define UTF8_REJECT 8

namespace {

static const unsigned char utf8d[] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 00..1f // NOLINT
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 20..3f // NOLINT
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 40..5f // NOLINT
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 60..7f // NOLINT
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9, // 80..9f // NOLINT
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, // a0..bf // NOLINT
  8,8,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, // c0..df // NOLINT
  0xa,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x4,0x3,0x3, // e0..ef // NOLINT
  0xb,0x6,0x6,0x6,0x5,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8, // f0..ff // NOLINT
  0x0,0x1,0x2,0x3,0x5,0x8,0x7,0x1,0x1,0x1,0x4,0x6,0x1,0x1,0x1,0x1, // s0..s0 // NOLINT
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,1, // s1..s2 // NOLINT
  1,2,1,1,1,1,1,2,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1, // s3..s4 // NOLINT
  1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,3,1,1,1,1,1,1, // s5..s6 // NOLINT
  1,3,1,1,1,1,1,3,1,3,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1, // s7..s8 // NOLINT
};

static uint32_t inline
decode_next(uint32_t* state, char32_t* code, unsigned char byte) {
  uint32_t type = utf8d[byte];

  *code = (*state != UTF8_ACCEPT) ?
    (byte & 0x3fu) | (*code << 6) :
    (0xff >> type) & (byte);

  *state = utf8d[256 + *state*16 + type];
  return *state;
}

// clang-format on
// Code copy end.

static size_t inline code_to_utf8(char32_t code, unsigned char* s) {
  if (code <= 0x7f) {  // 0xxxxxxx
    s[0] = code & 0xff;
    return 1;
  }
  if (code <= 0x7ff) {
    s[0] = 0xc0 | (code >> 6);    // 110xxxxx
    s[1] = 0x80 | (code & 0x3f);  // 10xxxxxx
    return 2;
  }
  if (code <= 0xffff) {
    s[0] = 0xe0 | (code >> 12);          // 1110xxxx
    s[1] = 0x80 | ((code >> 6) & 0x3f);  // 10xxxxxx
    s[2] = 0x80 | (code & 0x3f);         // 10xxxxxx
    return 3;
  }
  if (code <= 0x10ffff) {
    s[0] = 0xf0 | (code >> 18);           // 11110xxx
    s[1] = 0x80 | ((code >> 12) & 0x3f);  // 10xxxxxx
    s[2] = 0x80 | ((code >> 6) & 0x3f);   // 10xxxxxx
    s[3] = 0x80 | (code & 0x3f);          // 10xxxxxx
    return 4;
  }
  return 0;
}

static size_t inline code_bytes_size(char32_t code) {
  if (code <= 0x7f) return 1;
  if (code <= 0x7ff) return 2;
  if (code <= 0xffff) return 3;
  if (code <= 0x10ffff) return 4;
  return 0;
}

static uint32_t inline decode_next_naive(uint32_t* state, char32_t* code,
                                         unsigned char byte) {
  // state:
  // Ref: https://www.unicode.org/versions/corrigendum1.html
  // 0, starting to parse a new codepoint.
  // 8, invalid codepoint.
  // 1, wait for 1 more 80..BF
  // 2, wait for 2 more 80..BF
  // 3, wait for 3 more 80..BF
  // 4, the first byte is E0, wait for A0..BF, next state 1
  // 5, the first byte is F0, wait for 90..BF, next state 2
  // 6, the first byte is F4, wait for 80..8F, next state 2
  switch (*state) {
    case UTF8_ACCEPT:
      if (byte <= 0x7f) {
        // 0xxxxxxx, 00..7F, codepoint of 1 byte.
        *code = byte;
      } else if (byte < 0xc2) {
        // 80..c1 is invlaid to be a codepoint's first byte.
        *state = UTF8_REJECT;
      } else if (byte <= 0xdf) {
        // 110xxxxx, c2..DF, 1st byte of two
        // wait for 1 more 80..BF byte.
        *state = 1;
        *code = byte & 0x1f;
      } else if (byte == 0xe0) {
        // wait for A0..BF
        // 1st byte is 0xe0, total 3 bytes.
        *state = 4;
        *code = 0xe0 & 0xf;
      } else if (byte <= 0xef) {
        // 11100000, E1..EF, 1st of three
        // wait for 2 more 80..BF bytes.
        *state = 2;
        *code = byte & 0xf;
      } else if (byte == 0xf0) {
        // wait for 90..BF
        // 1st byte is 0xf0, total 4 bytes.
        *state = 5;
        *code = 0xf0 & 0x7;
      } else if (byte <= 0xf3) {
        // 11110000, F1..F3, 1st of four
        // wait for 3 more 80..BF bytes.
        *state = 3;
        *code = byte & 0x7;
      } else if (byte == 0xf4) {
        // wait for 80..8F
        *state = 6;
        *code = 0xf4 & 0x7;
      } else {
        *state = UTF8_REJECT;
      }
      break;
    // Continuation bytes:
    // state 1,2,3: 80..BF.
    // state 4: A0..BF
    // state 5: 90..BF
    // state 6: 80..8F
    case 1:
    case 2:
    case 3:
      if (byte >= 0x80 && byte <= 0xbf) {
        *state -= 1;
        *code = (*code << 6) | (byte & 0x3f);
      } else {
        *state = UTF8_REJECT;
      }
      break;
    case 4:
      if (byte >= 0xa0 && byte <= 0xbf) {
        *state = 1;
        *code = (*code << 6) | (byte & 0x3f);
      } else {
        *state = UTF8_REJECT;
      }
      break;
    case 5:
      if (byte >= 0x90 && byte <= 0xbf) {
        *state = 2;
        *code = (*code << 6) | (byte & 0x3f);
      } else {
        *state = UTF8_REJECT;
      }
      break;
    case 6:
      if (byte >= 0x80 && byte <= 0x8f) {
        *state = 2;
        *code = (*code << 6) | (byte & 0x3f);
      } else {
        *state = UTF8_REJECT;
      }
      break;
  }
  return *state;
}
}  // namespace

size_t simple_utf8::CountCodes(std::string_view s) {
  size_t k = 0;
  for (auto c : s) {
    if ((c & 0xc0) != 0x80) k++;
  }
  return k;
}

size_t simple_utf8::CountBytes(std::u32string_view p) {
  size_t j = 0;
  for (auto code : p)
    j += code_bytes_size(code);  // cppcheck-suppress useStlAlgorithm
  return j;
}

size_t simple_utf8::Decode(std::string_view s, std::u32string& p) {
  uint32_t state = 0;
  char32_t code = 0;
  size_t k = 0;
  for (auto c : s) {
    decode_next(&state, &code, c);
    if (state == UTF8_REJECT) return 0;  // early fail.
    if (state == UTF8_ACCEPT) p[k++] = code;
  }
  if (state != UTF8_ACCEPT) return 0;
  return k;
}

size_t simple_utf8::Encode(std::u32string_view p, std::string& s) {
  size_t j = 0;
  for (auto code : p) {
    auto d = code_to_utf8(code, reinterpret_cast<unsigned char*>(&s.at(j)));
    if (!d) return 0;
    j += d;
  }
  return j;
}

size_t simple_utf8::DecodeNaive(std::string_view s, std::u32string& p) {
  uint32_t state = 0;
  char32_t code = 0;
  size_t k = 0;
  for (auto c : s) {
    decode_next_naive(&state, &code, c);
    if (state == UTF8_REJECT) return 0;  // early fail.
    if (state == UTF8_ACCEPT) p[k++] = code;
  }
  if (state != UTF8_ACCEPT) return 0;
  return k;
}
