#pragma once

#if defined(size_t)
#else
typedef unsigned long size_t;
#endif

namespace task {

const int kStaticArraySize = 8;
using CmpFn = bool (*)(int, int);

enum class Task {
    Static = 1,
    Dynamic
};

enum class SortMethod {
    BubbleSort,
    SelectionSort
};

struct SortBenchmark {
    int swaps = 0;
    int comparisation = 0;
};

void Run();
void RunStaticTask();
void RunDynamicTask();

void ExecuteSortingTask(SortMethod sorting, CmpFn cmp, int* initialArr, size_t size);

void SelectionSort(CmpFn cmp, int* arr, size_t size, SortBenchmark& result);
void BubbleSort(CmpFn cmp, int* arr, size_t size, SortBenchmark& result);
}  // namespace task
