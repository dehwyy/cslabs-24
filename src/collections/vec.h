#pragma once
#include <cstddef>
#include <iostream>

namespace {
const int DEFAULT_CAPACITY = 10;
const int GROWTH_FACTOR = 2;
}  // namespace

namespace vec {
template<class T>
struct Vec {
    Vec() {
        {
            data = new T[DEFAULT_CAPACITY];
            size = 0;
            capacity = DEFAULT_CAPACITY;
        }
    }

    ~Vec() {
        if (this->data) {
            delete[] this->data;
        }
    }

    void push(T value) {
        if (this->size == this->capacity) {
            this->resize();
        }

        this->data[this->size] = value;
        this->size++;
    }
    void clear() {
        if (this->data != nullptr) {
            delete[] this->data;
        }

        this->size = 0;
        this->capacity = DEFAULT_CAPACITY;
        this->data = new T[DEFAULT_CAPACITY];
    }

    void extend(Vec<T> rhs) {
        for (size_t i = 0; i < rhs.len(); ++i) {
            this->push(rhs.get(i));
        }
    }

    void set(T item, size_t index) { this->data[index] = item; }

    T pop();

    T get(size_t index) const { return this->data[index]; }

    size_t len() const { return this->size; }

 private:
    T* data;
    size_t size;
    size_t capacity;

    friend std::ostream& operator<<(std::ostream& os, const Vec<T>& vector) {
        std::cout << '[';
        for (size_t i = 0; i < vector.size; ++i) {
            os << vector.data[i];

            if (i != vector.size - 1) {
                os << "|";
            }
        }
        os << ']';

        return os;
    }

    void resize() {
        capacity *= GROWTH_FACTOR;

        T* new_data = new T[capacity];

        std::copy(data, data + size, new_data);

        delete[] data;
        this->data = new_data;
    }
};
}  // namespace vec
