#include "task.h"
#include <iomanip>
#include <iostream>
#include "randmodule.h"

namespace {
bool CmpAsc(int a, int b) {
    return a < b;
}

bool CmpDesc(int a, int b) {
    return a > b;
}

void PrintArray(int* arr, size_t size, bool ln = false) {
    std::cout << "[";
    for (size_t i = 0; i < size; ++i) {
        std::cout << arr[i];

        if (i != size - 1) {
            std::cout << ",";
        }
    }
    std::cout << "]";

    if (ln) {
        std::cout << std::endl;
    }
}

void PrintInitialArray(int* arr, size_t size) {
    std::cout << "Исходный массив: ";

    PrintArray(arr, size, true);

    std::cout << std::endl;
}

void PrintArrayFormatted(int* arr, size_t size, task::SortMethod sortMethod, int swaps, int compares) {
    switch (sortMethod) {
        case task::SortMethod::SelectionSort:
            std::cout << "Сортировка выбором:   ";
            break;
        case task::SortMethod::BubbleSort:
            std::cout << "Сортировка пузырьком: ";
            break;
    }

    PrintArray(arr, size);
    std::cout << ", ";

    std::cout << "Перестановки: " << swaps << ", ";
    std::cout << "Сравнения: " << compares << ", ";

    std::cout << "\n" << std::endl;
}

}  // namespace

namespace task {
void Run() {
    int task = 0;

    std::cout << "Выберите задание: " << std::endl;
    std::cout << "1 - Сортировка статического массива" << std::endl;
    std::cout << "2 - Сортировка динамического массива" << std::endl;

    std::cout << "Ваш выбор: ";
    std::cin >> task;

    switch (static_cast<Task>(task)) {
        case Task::Static:
            RunStaticTask();
            break;
        case Task::Dynamic:
            RunDynamicTask();
            break;
        default:
            std::cout << "Неверной ввод заданий!" << std::endl;
    }
}

void RunStaticTask() {
    int staticArr[kStaticArraySize];
    randmodule::FillArrayWithRandomNumbers(staticArr, kStaticArraySize);

    PrintInitialArray(staticArr, kStaticArraySize);

    ExecuteSortingTask(SortMethod::BubbleSort, CmpAsc, staticArr, kStaticArraySize);
    ExecuteSortingTask(SortMethod::BubbleSort, CmpAsc, staticArr, kStaticArraySize);
    ExecuteSortingTask(SortMethod::BubbleSort, CmpDesc, staticArr, kStaticArraySize);

    ExecuteSortingTask(SortMethod::SelectionSort, CmpAsc, staticArr, kStaticArraySize);
    ExecuteSortingTask(SortMethod::SelectionSort, CmpAsc, staticArr, kStaticArraySize);
    ExecuteSortingTask(SortMethod::SelectionSort, CmpDesc, staticArr, kStaticArraySize);
}

void RunDynamicTask() {
    int size = 0;
    std::cout << "Размер массива: ";
    std::cin >> size;

    if (size <= 0) {
        std::cout << "Размер массива должен быть больше 0!" << std::endl;
        return;
    }

    int* dynamicArr = new int[size];
    randmodule::FillArrayWithRandomNumbers(dynamicArr, size);

    PrintInitialArray(dynamicArr, size);

    ExecuteSortingTask(SortMethod::BubbleSort, CmpAsc, dynamicArr, size);
    ExecuteSortingTask(SortMethod::SelectionSort, CmpAsc, dynamicArr, size);

    delete[] dynamicArr;
}

void ExecuteSortingTask(SortMethod sorting, CmpFn cmp, int* arr, size_t size) {
    if (!arr) {
        return;
    }

    SortBenchmark benchmark = {0, 0};

    switch (sorting) {
        case SortMethod::BubbleSort:
            BubbleSort(cmp, arr, size, benchmark);
            break;
        case SortMethod::SelectionSort:
            SelectionSort(cmp, arr, size, benchmark);
            break;
    }

    PrintArrayFormatted(arr, size, sorting, benchmark.swaps, benchmark.comparisation);
}

void SelectionSort(CmpFn cmp, int* arr, size_t size, SortBenchmark& benchmark) {
    if (!arr) {
        return;
    }

    for (size_t i = 0; i < size - 1; ++i) {
        size_t pivotIndex = i;

        for (size_t j = i + 1; j < size; ++j) {
            if (cmp(arr[j], arr[pivotIndex])) {
                pivotIndex = j;
            }
            ++benchmark.comparisation;
        }

        if (pivotIndex != i) {
            int temp = arr[i];
            arr[i] = arr[pivotIndex];
            arr[pivotIndex] = temp;

            ++benchmark.swaps;
        }
    }
}

void BubbleSort(CmpFn cmp, int* arr, size_t size, SortBenchmark& benchmark) {
    if (!arr) {
        return;
    };

    bool anySwapped = false;

    for (size_t i = 0; i < size - 1; ++i) {
        anySwapped = false;

        for (size_t j = 0; j < size - i - 1; ++j) {
            if (!cmp(arr[j], arr[j + 1])) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                anySwapped = true;

                ++benchmark.swaps;
            }

            ++benchmark.comparisation;
        }
        if (!anySwapped) {
            break;
        }
    }
}
}  // namespace task
