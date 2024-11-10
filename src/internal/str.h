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
    String(vec::Vec<char> v) {
        this->size = v.len();
        this->data = new char[this->size + 1];

        for (size_t i = 0; i < this->size; ++i) {
            this->data[i] = v.get(i);
        }

        this->data[this->size] = '\0';

        // std::cout << "\n __ String __" << std::endl;
        // std::cout << "size: " << this->size << std::endl;
        // std::cout << "data: " << this->data << std::endl;
        // std::cout << "Should be: " << v << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const String& s) {
        os << s.data;

        return os;
    }

    char* get();
    char* inner();
    char get_char(size_t i);
    size_t len();

 private:
    char* data;
    size_t size;
};
}  // namespace str
