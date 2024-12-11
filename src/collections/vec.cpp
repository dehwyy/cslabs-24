#include "vec.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>

namespace {

const size_t kDefaultVectorSize = 8;
const size_t kGrowthFactor = 2;

void ResizeVector(vec::VecInt& vector) {
    vector.capacity *= kGrowthFactor;

    int* buffer = new int[vector.capacity];
    std::copy(vector.vector, vector.vector + vector.size, buffer);

    delete[] vector.vector;

    vector.vector = buffer;
}

}  // namespace

namespace vec {

VecInt CreateVector() {
    int* array = new int[kDefaultVectorSize];

    return {.size = 0, .capacity = kDefaultVectorSize, .vector = array};
}

void ClearVector(VecInt& vector) {
    vector.size = 0;
    delete[] vector.vector;

    vector.vector = new int[kDefaultVectorSize];
    vector.capacity = kDefaultVectorSize;
}

void DeleteVector(VecInt& vector) {
    vector.size = 0;
    vector.capacity = 0;

    delete[] vector.vector;

    vector.vector = nullptr;
}

int& GetElement(const VecInt& vector, size_t index) {
    return vector.vector[index];
}

void Push(VecInt& vector, int element) {
    if (vector.size >= vector.capacity) {
        ResizeVector(vector);
    }

    vector.vector[vector.size++] = element;
}

}  // namespace vec
