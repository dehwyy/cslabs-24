#include "str.h"
#include <iostream>

namespace str {
char String::get_char(size_t i) const {
    return this->data[i];
}
char* String::get() const {
    return this->data;
}

char* String::inner() const {
    return this->data;
}

size_t String::len() const {
    return this->size;
}

vec::Vec<String> Split(String s) {
    auto buf = vec::Vec<String>();

    auto word = vec::Vec<char>();
    for (size_t i = 0; i < s.len(); ++i) {
        if (std::ispunct(s.get_char(i)) || std::isspace(s.get_char(i))) {
            if (word.len() != 0) {
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

vec::Vec<String> GroupedBy(const String& s, size_t group_size) {
    auto buf = vec::Vec<String>();
    char* group = new char[group_size + 1];

    for (size_t i = 0; i < s.len(); i += group_size) {
        // if (i >= this->size) {
        //     i = this->size - 1;
        // }

        std::strncpy(group, s.get() + i, group_size);
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

        // std::cout << "\nDEBUG START" << std::endl;
        // std::cout << "DAta temp: " << data_buf << std::endl;
        // std::cout << "DAta: " << s.inner() << std::endl;
        // std::cout << "DAta len: " << s.len() << std::endl;
        // std::cout << "DAta temp len: " << strlen(data_buf) << std::endl;
        // std::cout << "DEBUG END" << std::endl;
    }

    data_buf[write_len] = '\0';

    auto s = String(data_buf);
    delete[] data_buf;

    return s;
}

}  // namespace str
