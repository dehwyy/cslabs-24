#include <iostream>
#include "randmodule.h"

namespace {
  typedef bool (*CmpFn)(int, int);

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
}

namespace task {

void PrintArray(int* arr, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
}

void Run() {
  const size_t size = randmodule::FromRange(5, 10);
  int* arr = new int[size];

  void(*Sort)(bool(*)(int, int), int*, size_t) = SelectionSort;

  randmodule::FillArrayWithRandomNumbers(arr, size);
  PrintArray(arr, size);

  Sort(CmpAsc, arr, size);
  PrintArray(arr, size);

  Sort(CmpDesc, arr, size);
  PrintArray(arr, size);

  BubbleSort(CmpAsc, arr, size);
  PrintArray(arr, size);

  delete[] arr;
}

}
