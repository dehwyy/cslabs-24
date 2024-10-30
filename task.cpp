#include <iostream>
#include "randmodule.h"

namespace {
using CmpFn = bool (*)(int, int);

enum class SortMethod {
    Selection = 1,
    Bubble
};

void SelectionSort(CmpFn cmp, int* arr, size_t size) {
    for (size_t i = 0; i < size - 1; ++i) {
        size_t pivotIndex = i;

        for (size_t j = i + 1; j < size; ++j) {
            if (cmp(arr[j], arr[pivotIndex])) {
                pivotIndex = j;
            }
        }

        if (pivotIndex != i) {
            int temp = arr[i];
            arr[i] = arr[pivotIndex];
            arr[pivotIndex] = temp;
        }
    }
}

void BubbleSort(CmpFn cmp, int* arr, size_t size) {
    bool anySwapped = false;

    for (size_t i = 0; i < size - 1; ++i) {
        anySwapped = false;

        for (size_t j = 0; j < size - i - 1; ++j) {
            if (!cmp(arr[j], arr[j + 1])) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                anySwapped = true;
            }
        }
        if (!anySwapped) {
            break;
        }
    }
}

bool CmpAsc(int a, int b) {
    return a < b;
}

bool CmpDesc(int a, int b) {
    return a > b;
}

void CopyIntArray(int* from, int* to, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        to[i] = from[i];
    }
}

void PrintArray(int* arr, size_t size, SortMethod sortMethod = SortMethod::Bubble, int swaps = 0, int compares = 0) {
    switch (sortMethod) {
        case SortMethod::Selection:
            std::cout << "Выбором";
            break;
        case SortMethod::Bubble:
            std::cout << "Пузырьком";
            break;
    }

    std::cout << "[";
    for (size_t i = 0; i < size; ++i) {
        std::cout << arr[i] << ", ";
    }
    std::cout << "]";
    std::cout << swaps << compares << std::endl;
}

void ArraySortAndPrint(SortMethod sortMethod, CmpFn cmp, int* arr, size_t size) {
    switch (sortMethod) {
        case SortMethod::Selection:
            break;
        case SortMethod::Bubble:
            break;
    };
}

}  // namespace

namespace task {

void Run() {
    const size_t size = randmodule::FromRange(5, 10);
    int* arr = new int[size];
    randmodule::FillArrayWithRandomNumbers(arr, size);
    int* arr2 = new int[size];

    PrintArray(arr, size);

    SelectionSort(CmpAsc, arr, size);

    PrintArray(arr, size);

    PrintArray(arr, size);

    PrintArray(arr, size);

    BubbleSort(CmpAsc, arr, size);
    PrintArray(arr, size);

    delete[] arr;
    delete[] arr2;
}

}  // namespace task
