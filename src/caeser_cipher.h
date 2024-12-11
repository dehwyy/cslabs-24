#pragma once
#include <cstddef>
#include "collections/vec.h"

namespace CaesarCipher {
vec::VecInt CreateNotebookKeys(const char* notebook);
char* Encode(const char* text, const vec::VecInt& keys);
char* Decode(const char* encodedText, const vec::VecInt& keys);
void GenerateStatistics(const char* originalText, const char* encodedText, const vec::VecInt& keys);
}  // namespace CaesarCipher
