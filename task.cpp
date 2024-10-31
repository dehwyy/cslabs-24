#include "task.h"
#include <iostream>
#include "randmodule.h"

namespace {
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

void PrintArrayIsNullptr() {
    std::cout << "Ошибка! Указатель на массив = nullptr!" << std::endl;
}

void PrintArrayElements(int* arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        std::cout << arr[i] << ", ";
    }
}

void PrintArray(int* arr, size_t size, task::SortMethod sortMethod, int swaps, int compares) {
    switch (sortMethod) {
        case task::SortMethod::SelectionSort:
            std::cout << "SelectionSort ";
            break;
        case task::SortMethod::BubbleSort:
            std::cout << "BubbleSort ";
            break;
    }

    std::cout << "[";
    PrintArrayElements(arr, size);
    std::cout << "]";
    std::cout << swaps << compares << std::endl;
}

void SortAndPrintArray(task::SortMethod sortMethod, task::CmpFn cmp, int* arr, size_t size) {
    task::SortResult* result = {};

    switch (sortMethod) {
        case task::SortMethod::SelectionSort:
            result = task::SelectionSort(cmp, arr, size);
            break;
        case task::SortMethod::BubbleSort:
            result = task::BubbleSort(cmp, arr, size);
            break;
    };

    if (!result) {
        PrintArrayIsNullptr();
        return;
    }

    PrintArray(arr, size, sortMethod, (*result).swaps, (*result).comparisation);
}

int* CopyIntArray(int* from, size_t size) {
    if (!from) {
        PrintArrayIsNullptr();
        return nullptr;
    }

    int* array_copy = new int[size];

    for (size_t i = 0; i < size; ++i) {
        array_copy[i] = from[i];
    }

    return array_copy;
}

}  // namespace

namespace task {
void Run() {
    int task = 0;
    switch (static_cast<Task>(task)) {
        case Task::Static:

            int static_arr[kStaticArraySize];
            randmodule::FillArrayWithRandomNumbers(static_arr, kStaticArraySize);

            PrintArrayElements(static_arr, kStaticArraySize);

            SortAndPrintArray(SortMethod::BubbleSort, CmpAsc, CopyIntArray(static_arr, kStaticArraySize), kStaticArraySize);
            SortAndPrintArray(SortMethod::BubbleSort, CmpAsc, CopyIntArray(static_arr, kStaticArraySize), kStaticArraySize);
            SortAndPrintArray(SortMethod::BubbleSort, CmpDesc, CopyIntArray(static_arr, kStaticArraySize), kStaticArraySize);

            SortAndPrintArray(SortMethod::SelectionSort, CmpAsc, CopyIntArray(static_arr, kStaticArraySize), kStaticArraySize);
            SortAndPrintArray(SortMethod::SelectionSort, CmpAsc, CopyIntArray(static_arr, kStaticArraySize), kStaticArraySize);
            SortAndPrintArray(SortMethod::SelectionSort, CmpDesc, CopyIntArray(static_arr, kStaticArraySize), kStaticArraySize);

            break;
        case Task::Dynamic:
            break;
        default:
            std::cout << "Неверной ввод заданий!" << std::endl;
    }
}

SortResult* SelectionSort(CmpFn cmp, int* arr, size_t size) {
    if (!arr) {
        return nullptr;
    }

    SortResult result = SortResult{0, 0};

    for (size_t i = 0; i < size - 1; ++i) {
        size_t pivotIndex = i;

        for (size_t j = i + 1; j < size; ++j) {
            if (cmp(arr[j], arr[pivotIndex])) {
                pivotIndex = j;
            }
            ++result.comparisation;
        }

        if (pivotIndex != i) {
            int temp = arr[i];
            arr[i] = arr[pivotIndex];
            arr[pivotIndex] = temp;

            ++result.swaps;
        }
    }

    return &result;
}

SortResult* BubbleSort(CmpFn cmp, int* arr, size_t size) {
    if (!arr) {
        return nullptr;
    };

    SortResult result = SortResult{0, 0};
    bool anySwapped = false;

    for (size_t i = 0; i < size - 1; ++i) {
        anySwapped = false;

        for (size_t j = 0; j < size - i - 1; ++j) {
            if (!cmp(arr[j], arr[j + 1])) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                anySwapped = true;

                ++result.swaps;
            }

            ++result.comparisation;
        }
        if (!anySwapped) {
            break;
        }
    }

    return &result;
}
}  // namespace task
