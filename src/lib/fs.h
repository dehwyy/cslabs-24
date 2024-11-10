#pragma once
#include "../collections/str.h"
#include "../collections/vec.h"
#include "fstream"

namespace fs {
vec::Vec<str::String> ReadAllVec(const str::String& filename, unsigned read_by);
void WriteAllVec(const str::String& filename, vec::Vec<str::String>& buf);
}  // namespace fs
