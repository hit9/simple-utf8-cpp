simple-utf8-cpp
===============

Tiny simple library to convert between utf8 bytes and char32_t codepoints in C++.

Reference
---------

The decoder is based on statemachine approach:
https://bjoern.hoehrmann.de/utf-8/decoder/dfa.

Requirements
------------

No external dependencies except a compiler that supports at least C++17.

Example
-------

```cpp
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
```

Run tests
---------

```
cmake -B build -S .
make -C build tests
./build/tests/tests
```

License
-------

```
Copyright (c) 2023 Chao Wang <hit9@icloud.com> for this library.
Copyright (c) 2008-2009 Bjoern Hoehrmann <bjoern@hoehrmann.de> for the utf8 dfa decoder.
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
```
