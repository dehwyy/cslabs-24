#pragma once
#include <cstring>
#include <iostream>
#include "vec.h"

namespace str {
struct String {
    String() : data(nullptr), size(0) {}
    String(char const* v) : data(const_cast<char*>(v)), size(strlen(v)) {}  // TODO: remove?
    String(char* v) {
        this->size = std::strlen(v);
        this->data = new char[this->size + 1];
        std::strncpy(this->data, v, this->size + 1);
    }
    String(const vec::Vec<char>& v) {
        // std::cout << "Vec! with len: " << v << " with " << v.len();
        this->size = v.len();
        this->data = new char[this->size + 1];

        for (size_t i = 0; i < this->size; ++i) {
            this->data[i] = v.get(i);
        }

        this->data[this->size] = '\0';

        // std::cout << " " << this->data << std::endl;
        // std::cout << "\n __ String __" << std::endl;
        // std::cout << "size: " << this->size << std::endl;
        // std::cout << "data: " << this->data << std::endl;
        // std::cout << "Should be: " << v << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const String& s) {
        os << s.data;

        return os;
    }

    char* get() const;
    char* inner() const;
    char get_char(size_t i) const;
    size_t len() const;

 private:
    char* data;
    size_t size;
};

String Joined(const vec::Vec<String>& str_vec);

String Slice(const String& s, size_t start);
String Slice(const String& s, size_t start, size_t end);

vec::Vec<String> GroupedBy(const String& s, size_t group_size);
vec::Vec<String> Split(String s);
vec::Vec<String> Split(String s, String delimeter);

bool Equals(String s1, String s2);
bool StartsWith(String s, String prefix);

}  // namespace str
