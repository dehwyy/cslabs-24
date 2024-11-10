#include "fs.h"
#include "iostream"

namespace {
std::istream& read(std::ifstream& f, char* buf, unsigned size, bool with_punct) {
    if (with_punct) {
        return f.get(buf, size + 1);
    } else {
        return f.getline(buf, size + 1, '\n');
    }
}
}  // namespace

namespace fs {
void File::ReadAll(vec::Vec<str::String>& buf, unsigned read_by, bool with_punct) {
    std::ifstream f(filepath.get(), std::ios::binary);

    if (!f.is_open()) {
        std::cerr << "Failed to open file: " << filepath.get() << std::endl;
        exit(1);
        return;
    }

    char* read_buf = new char[read_by + 1];

    while (read(f, read_buf, read_by, with_punct) || !f.eof()) {
        char* word_buf = new char[read_by + 1];

        size_t word_i = 0;
        for (size_t i = 0; i < std::strlen(read_buf); ++i) {
            char ch = read_buf[i];
            if (!(std::ispunct(ch) || std::isspace(ch)) || with_punct) {
                word_buf[word_i] = ch;
                ++word_i;
            }
        }

        word_buf[word_i] = '\0';

        buf.push(str::String(word_buf));

        f.clear();
        delete[] word_buf;
    }

    delete[] read_buf;

    f.close();
}

void File::WriteAll(vec::Vec<str::String>& buf) {
    std::ofstream f(filepath.get(), std::ios::binary | std::ios::trunc | std::ios::out);

    if (!f.is_open()) {
        std::cerr << "Failed to open file: " << filepath.get() << std::endl;
        exit(1);
        return;
    }

    for (size_t i = 0; i < buf.len(); i++) {
        auto s = buf.get(i);

        f.write(s.inner(), static_cast<std::streamsize>(s.len()));
    }

    f.close();
}
}  // namespace fs
