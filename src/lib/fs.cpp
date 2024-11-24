#include "fs.h"
#include "iostream"

namespace {
void HandleOpenError(const str::String& filepath, bool is_open) {
    if (!is_open) {
        std::cerr << "Failed to open file: " << str::AsCStr(filepath) << std::endl;
        exit(1);
    }
}
}  // namespace

namespace fs {
vec::Vec<str::String> ReadAllVec(const str::String& filepath, unsigned read_by) {
    auto buf = vec::Vec<str::String>();
    std::ifstream f(str::AsCStr(filepath), std::ios::binary);

    HandleOpenError(filepath, f.is_open());

    char* read_buf = new char[read_by + 1];

    while (true) {
        f.read(read_buf, read_by);
        if (f.gcount() == 0) {
            break;
        }

        read_buf[f.gcount()] = '\0';

        auto s = str::FromCStr(read_buf);
        if (str::Len(s) != 0) {
            buf.push(s);
        }

        f.clear();
    }

    delete[] read_buf;

    f.close();

    return buf;
}

void WriteAllVec(const str::String& filepath, vec::Vec<str::String>& buf) {
    std::ofstream f(str::AsCStr(filepath), std::ios::binary | std::ios::trunc | std::ios::out);

    HandleOpenError(filepath, f.is_open());

    for (size_t i = 0; i < buf.len(); i++) {
        auto s = buf.get(i);

        f.write(str::AsCStr(s), static_cast<std::streamsize>(str::Len(s)));
    }

    f.close();
}
}  // namespace fs
