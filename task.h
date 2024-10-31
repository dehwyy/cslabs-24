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

struct SortResult {
    int swaps = 0;
    int comparisation = 0;
};

void Run();

[[nodiscard]] SortResult* SelectionSort(CmpFn cmp, int* arr, unsigned size);
[[nodiscard]] SortResult* BubbleSort(CmpFn cmp, int* arr, unsigned size);
}
