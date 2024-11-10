#pragma once
#include "fstream"
#include "str.h"
#include "vec.h"

namespace fs {
struct File {
    str::String filepath;
    void* file_data;

    File(str::String path) : filepath(path), file_data(nullptr) {};

    void ReadAll(vec::Vec<str::String>&, unsigned, bool with_punct = false);
    void WriteAll(vec::Vec<str::String>&);
};
}  // namespace fs
