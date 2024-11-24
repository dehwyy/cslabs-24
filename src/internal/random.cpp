#include <random>

namespace {}  // namespace

namespace randmodule {
double FromRange(double begin, double end) {
    std::random_device r{};
    std::default_random_engine randomEngine(r());
    std::uniform_real_distribution<double> distribution(begin, end);

    return distribution(randomEngine);
}

}  // namespace randmodule
