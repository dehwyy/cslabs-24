#include "str.h"
#include <iostream>

namespace str {
char String::get_char(size_t i) const {
    return this->data[i];
}
char* String::inner() const {
    return this->data;
}

size_t String::len() const {
    return this->size;
}

String Slice(const String& s, size_t start) {
    return Slice(s, start, s.len());
}

String Slice(const String& s, size_t start, size_t end) {
    auto slice = new char[end - start + 1];
    std::strncpy(slice, s.inner() + start, end - start);
    slice[end - start] = '\0';

    auto str = String(slice);
    delete[] slice;

    return str;
}

vec::Vec<String> Split(String s) {
    auto buf = vec::Vec<String>();

    auto word = vec::Vec<char>();
    for (size_t i = 0; i < s.len(); ++i) {
        if (std::ispunct(s.get_char(i)) || std::isspace(s.get_char(i))) {
            if (word.len() > 0) {
                buf.push(String(word));
                word.clear();
            }
            continue;
        }

        word.push(s.get_char(i));
    }

    if (word.len() != 0) {
        buf.push(String(word));
    }

    return buf;
}

vec::Vec<String> Split(String s, String delimeter) {
    auto output = vec::Vec<String>();

    auto buf = vec::Vec<char>();
    for (size_t i = 0; i < s.len() - delimeter.len() + 1; ++i) {
        if (!std::strncmp(s.inner() + i, delimeter.inner(), delimeter.len())) {
            if (buf.len() != 0) {
                output.push(String(buf));
                buf.clear();
            }

            i += delimeter.len() - 1;
        } else {
            buf.push(s.get_char(i));
        }
    }

    output.push(String(buf));

    return output;
}

vec::Vec<String> GroupedBy(const String& s, size_t group_size) {
    auto buf = vec::Vec<String>();
    char* group = new char[group_size + 1];

    for (size_t i = 0; i < s.len(); i += group_size) {
        std::strncpy(group, s.inner() + i, group_size);
        group[group_size] = '\0';
        buf.push(group);
    }

    delete[] group;
    return buf;
}

String Joined(const vec::Vec<String>& str_vec) {
    size_t len = 0;

    for (size_t i = 0; i < str_vec.len(); ++i) {
        len += str_vec.get(i).len();
    }

    auto data_buf = new char[len + 1];
    size_t write_len = 0;
    for (size_t i = 0; i < str_vec.len(); ++i) {
        auto s = str_vec.get(i);
        std::strncpy(data_buf + write_len, s.inner(), s.len());
        write_len += s.len();
    }

    data_buf[write_len] = '\0';

    auto s = String(data_buf);
    delete[] data_buf;

    return s;
}

bool Equals(String s1, String s2) {
    return !std::strcmp(s1.inner(), s2.inner());
}

bool StartsWith(String s, String prefix) {
    return !std::strncmp(s.inner(), prefix.inner(), prefix.len());
}

}  // namespace str
