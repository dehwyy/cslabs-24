#include "str.h"

namespace str {
char String::get_char(size_t i) {
    if (i >= size) {
        std::cout << "Index out of range" << std::endl;
        exit(1);
    }

    return this->data[i];
}
char* String::get() {
    return this->data;
}

char* String::inner() {
    return this->data;
}

size_t String::len() {
    return this->size;
}
}  // namespace str
