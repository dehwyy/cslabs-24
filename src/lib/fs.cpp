#include "fs.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace {
void HandleOpenError(const char* filename, bool is_open) {
    if (!is_open) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        exit(1);
    }
}
}  // namespace

namespace fs {
void WriteFile(const char* filename, const char* content) {
    // Открыть файл
    std::ofstream file(filename, std::ios::binary | std::ios::trunc | std::ios::out);
    HandleOpenError(filename, file.is_open());

    // Записать содержимое файла
    file.write(content, std::strlen(content));

    file.close();
}

char* ReadFile(const char* filename) {
    // Открыть файл
    std::ifstream file(filename, std::ios::binary);
    HandleOpenError(filename, file.is_open());

    // Получить размер файла
    file.seekg(0, std::ios::end);
    size_t size = static_cast<size_t>(file.tellg());
    file.seekg(0, std::ios::beg);

    // Считать содержимое файла
    char* content = new char[size + 1];
    file.read(content, size);
    content[size] = '\0';

    file.close();

    return content;
}
}  // namespace fs
