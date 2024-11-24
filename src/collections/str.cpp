#include "str.h"
#include <iostream>

namespace str {
String NewString() {
    return String{.data = nullptr, .size = 0};
}

String FromCStr(char* s) {
    if (s) {
        size_t len = std::strlen(s);
        char* s_copy = new char[len + 1];
        std::strncpy(s_copy, s, len + 1);

        return String{.data = s_copy, .size = len};
    }

    return NewString();
}

String FromStaticCStr(const char* s) {
    size_t len = std::strlen(s);
    // Making the copy of the const string.
    char* s_copy = new char[len + 1];
    std::strncpy(s_copy, s, len + 1);

    return String{.data = s_copy, .size = len};
}

String FromVec(const vec::Vec<char>& vector) {
    size_t len = vector.len();

    // Making the copy of the vector data.
    char* vector_copy = new char[len + 1];
    for (size_t i = 0; i < len; ++i) {
        vector_copy[i] = vector.get(i);
    }
    // Add null terminator.
    vector_copy[len] = '\0';

    return String{.data = vector_copy, .size = vector.len()};
}

char* AsCStr(const String& s) {
    return s.data;
}

char GetChar(const String& s, size_t idx) {
    return s.data[idx];
}

size_t Len(const String& s) {
    return s.size;
}

String Joined(const vec::Vec<String>& str_vec) {
    size_t len = 0;

    for (size_t i = 0; i < str_vec.len(); ++i) {
        len += Len(str_vec.get(i));
    }

    auto data_buf = new char[len + 1];
    size_t write_len = 0;
    for (size_t i = 0; i < str_vec.len(); ++i) {
        auto s = str_vec.get(i);
        std::strncpy(data_buf + write_len, AsCStr(s), Len(s));
        write_len += Len(s);
    }

    data_buf[write_len] = '\0';

    auto s = FromCStr(data_buf);
    delete[] data_buf;

    return s;
}

String Slice(const String& s, size_t start) {
    return Slice(s, start, Len(s));
}

String Slice(const String& s, size_t start, size_t end) {
    auto slice = new char[end - start + 1];
    std::strncpy(slice, AsCStr(s) + start, end - start);
    slice[end - start] = '\0';

    auto str = FromCStr(slice);
    delete[] slice;

    return str;
}

vec::Vec<String> GroupedBy(const String& s, size_t group_size) {
    auto buf = vec::Vec<String>();
    char* group = new char[group_size + 1];

    for (size_t i = 0; i < Len(s); i += group_size) {
        std::strncpy(group, AsCStr(s) + i, group_size);
        group[group_size] = '\0';
        buf.push(FromCStr(group));
    }

    delete[] group;
    return buf;
}

vec::Vec<String> Split(String s) {
    auto buf = vec::Vec<String>();

    auto word = vec::Vec<char>();
    for (size_t i = 0; i < Len(s); ++i) {
        if (std::ispunct(GetChar(s, i)) || std::isspace(GetChar(s, i))) {
            if (word.len() > 0) {
                buf.push(FromVec(word));
                word.clear();
            }
            continue;
        }

        word.push(GetChar(s, i));
    }

    if (word.len() != 0) {
        buf.push(FromVec(word));
    }

    return buf;
}

vec::Vec<String> Split(String s, String delimeter) {
    auto output = vec::Vec<String>();

    auto buf = vec::Vec<char>();
    for (size_t i = 0; i < Len(s) - Len(delimeter) + 1; ++i) {
        if (!std::strncmp(AsCStr(s) + i, AsCStr(delimeter), Len(delimeter))) {
            if (buf.len() != 0) {
                output.push(FromVec(buf));
                buf.clear();
            }

            i += Len(delimeter) - 1;
        } else {
            buf.push(GetChar(s, i));
        }
    }

    output.push(FromVec(buf));

    return output;
}

bool Equals(String s1, String s2) {
    return !std::strcmp(AsCStr(s1), AsCStr(s2));
}

bool StartsWith(String s, String prefix) {
    return !std::strncmp(AsCStr(s), AsCStr(prefix), Len(prefix));
}

}  // namespace str
