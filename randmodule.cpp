#include <random>

namespace {
const int RANDOM_RANGE_BEGIN = 0;
const int RANDOM_RANGE_END = 99;
}  // namespace

namespace randmodule {
void FillArrayWithRandomNumbers(int* arr, size_t size) {
    std::random_device r{};
    std::default_random_engine randomEngine(r());
    std::uniform_int_distribution<int> distribution(RANDOM_RANGE_BEGIN, RANDOM_RANGE_END);

    for (int i = 0; i < size; ++i) {
        arr[i] = distribution(randomEngine);
    }
}

[[nodiscard]] int FromRange(int begin, int end) {
    std::random_device r{};
    std::default_random_engine randomEngine(r());
    std::uniform_int_distribution<int> distribution(begin, end);

    return distribution(randomEngine);
}

}  // namespace randmodule
