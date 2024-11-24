#include "derivation.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include "internal/random.h"

namespace {

const int kWidthColumn = 20;
const int kColumnsQuantity = 4;
const int kMaxIter = 100000;

const double kMinA = 0.;
const double kMaxA = 1.;
const double kMinB = 2.;
const double kMaxB = 3.;

[[nodiscard]] double f1(double x) {
    return x;
}

[[nodiscard]] double f2(double x) {
    return std::sin(22 * x);
}

[[nodiscard]] double f3(double x) {
    return std::pow(x, 4);
}

[[nodiscard]] double f4(double x) {
    return std::atan(x);
}

void PrintTable(derivation::IntegralPrint integralPrint[]) {
    std::cout << std::setw(kWidthColumn) << "Function name" << std::setw(kWidthColumn) << "Calculated Sum" << std::setw(kWidthColumn) << "Actual Sum"
              << std::setw(kWidthColumn) << "N" << std::endl;

    for (int i = 0; i < kColumnsQuantity; i++) {
        std::cout << std::setw(kWidthColumn) << integralPrint[i].fn_name << std::setw(kWidthColumn) << integralPrint[i].integral_sum
                  << std::setw(kWidthColumn) << integralPrint[i].actual_integral_sum << std::setw(kWidthColumn) << integralPrint[i].n << std::endl;
    }

    std::cout << std::endl;
}

[[nodiscard]] double IntRect(double (*f)(double), double a, double b, double epsilon, int& n) {
    n = 1;
    double h = b - a;
    double integral = 0.;
    double previous_integral = 0.;

    while (n < kMaxIter) {
        integral = 0.;

        for (int i = 0; i < n; ++i) {
            integral += f(a + i * h) * h;
        }

        if (n > 1 && std::fabs(integral - previous_integral) < epsilon) {
            break;
        }

        previous_integral = integral;
        n *= 2;
        h /= 2;
    }

    return integral;
}

[[nodiscard]] double IntTrap(double (*f)(double), double a, double b, double epsilon, int& n) {
    n = 1;
    double h = b - a;
    double integral = 0;
    double previous_integral = 0;

    while (n < kMaxIter) {
        integral = 0.0;
        for (int i = 0; i < n; ++i) {
            double x = a + i * h;
            integral += (f(x) + f(x + h)) * h / 2;
        }

        if (n > 1 && std::fabs(integral - previous_integral) < epsilon) {
            break;
        }

        previous_integral = integral;

        n *= 2;
        h /= 2;
    }

    return integral;
}

}  // namespace

namespace derivation {
void Run() {
    double a = randmodule::FromRange(kMinA, kMaxA);
    double b = randmodule::FromRange(kMinB, kMaxB);

    std::cout << "a: " << a << " b: " << b << std::endl;

    double epsilon = 0.01;
    int n = 1;
    for (int i = 0; i <= 4; ++i) {
        IntegralPrint integral_print[4];
        integral_print[0].fn_name = "y = x        ";
        integral_print[0].integral_sum = IntRect(f1, a, b, epsilon, n);
        integral_print[0].actual_integral_sum = (std::pow(b, 2) - std::pow(a, 2)) / 2.0;
        integral_print[0].n = n;

        integral_print[1].fn_name = "y = sin(22x) ";
        integral_print[1].integral_sum = IntRect(f2, a, b, epsilon, n);
        integral_print[1].actual_integral_sum = (std::cos(a * 22.0) - std::cos(b * 22.0)) / 22.0;
        integral_print[1].n = n;
        integral_print[2].fn_name = "y = x^4      ";
        integral_print[2].integral_sum = IntRect(f3, a, b, epsilon, n);
        integral_print[2].actual_integral_sum = (std::pow(b, 5) - std::pow(a, 5)) / 5.0;
        integral_print[2].n = n;
        integral_print[3].fn_name = "y = arctan(x)";
        integral_print[3].integral_sum = IntRect(f4, a, b, epsilon, n);
        integral_print[3].actual_integral_sum =
            b * std::atan(b) - a * std::atan(a) - (std::log(std::pow(b, 3) + 1) - std::log(std::pow(a, 2) + 1)) / 2.0;
        integral_print[3].n = n;

        std::cout << "Метод прямоугольников. epsilon = " << std::resetiosflags(std::ios::fixed) << epsilon << std::endl;
        PrintTable(integral_print);

        integral_print[0].actual_integral_sum = IntTrap(f1, a, b, epsilon, n);
        integral_print[1].actual_integral_sum = IntTrap(f2, a, b, epsilon, n);
        integral_print[2].actual_integral_sum = IntTrap(f3, a, b, epsilon, n);
        integral_print[3].actual_integral_sum = IntTrap(f4, a, b, epsilon, n);

        std::cout << "Метод трапеций. epsilon = " << std::resetiosflags(std::ios::fixed) << epsilon << std::endl;
        PrintTable(integral_print);

        epsilon = epsilon / 10;
    }
}
}  // namespace derivation
