#pragma once

#include <cstddef>

namespace vec {

struct VecInt {
    size_t size{};
    size_t capacity{};
    int* vector{};
};

VecInt CreateVector();
void ClearVector(VecInt& vector);
void DeleteVector(VecInt& vector);

int& GetElement(const VecInt& vector, size_t index);
void Push(VecInt& vector, int element);
}  // namespace vec
