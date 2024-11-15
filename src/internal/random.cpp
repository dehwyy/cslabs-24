#include <random>

namespace {}  // namespace

namespace randmodule {
[[nodiscard]] int FromRange(int begin, int end) {
    std::random_device r{};
    std::default_random_engine randomEngine(r());
    std::uniform_int_distribution<int> distribution(begin, end);

    return distribution(randomEngine);
}

}  // namespace randmodule
