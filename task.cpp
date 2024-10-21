#define PI M_PI
#include <cmath>
#include <iostream>

namespace {
const int kMaxIterations = 1e5;
const double kIterativeX0 = 0.1;

enum class Task : int {
    Iteration = 1,
    Newton = 2,
    HalfDivision = 3
};

bool IsValidTaskNumber(int task) {
    bool isValid = false;

    switch (static_cast<Task>(task)) {
        case Task::Iteration:
            isValid = true;
            break;
        case Task::Newton:
            isValid = true;
            break;
        case Task::HalfDivision:
            isValid = true;
            break;
    }

    return isValid;
}

double f(double x, double k) {
    return k * std::cos(x);
}

double fx(double x, double k) {
    return x - f(x, k);
}

double fpx(double x, double k) {
    return 1 + k * std::sin(x);
}

double IterativeMethod(double epsilon, double k, int& n) {
    double x0 = kIterativeX0;
    double x = f(x0, k);

    while (std::abs(x0 - x) > epsilon && n < kMaxIterations) {
        x0 = x;
        x = f(x0, k);
        ++n;
    }

    return x0;
}

double NewtonMethod(double epsilon, double k, int& n) {
    double x0 = 1.;
    while (std::abs(f(x0, k)) > epsilon && n < kMaxIterations) {
        x0 = x0 - fx(x0, k) / fpx(x0, k);
        ++n;
    }

    return x0;
}

double HalfDivision(double epsilon, double k, int& n, double l, double r) {
    double c = (l + r) / 2;

    while (r - l > epsilon) {
        double fl = fx(l, k);
        double fc = fx(c, k);

        if ((fc >= 0 && fl <= 0) || (fc <= 0 && fl >= 0)) {
            r = c;
        } else {
            l = c;
        }
        c = (l + r) / 2;
        ++n;
    }

    return c;
}

double ReadEpsilon() {
    double epsilon = 0;
    std::cout << "Введите точность: ";
    std::cin >> epsilon;
    return epsilon;
}

double ReadK() {
    double k = 0;
    std::cout << "Введите коэффициент: ";
    std::cin >> k;
    return k;
}

}  // namespace

namespace task {
void Run() {
    std::cout << "Выберите задание:\n"
              << "1 - Итерационный метод\n"
              << "2 - Метод Ньютона\n"
              << "3 - Метод половинного деления\n"
              << "Ваш выбор: ";

    int task = 0;
    std::cin >> task;

    while (!IsValidTaskNumber(task)) {
        std::cout << "Неверный ввод номера задания! Введите еще раз: \n";
        std::cin >> task;
    }

    Task castedTask = static_cast<Task>(task);

    double epsilon = ReadEpsilon();
    double k = ReadK();
    int n = 0;

    switch (castedTask) {
        case Task::Iteration:
            std::cout << "Результат итерационного метода, ε = " << epsilon << ", k = " << k << ": \nx = " << IterativeMethod(epsilon, k, n)
                      << "\nКоличество итераций: " << n << std::endl;
            break;
        case Task::Newton:
            std::cout << "Результат метода Ньютона, ε = " << epsilon << ", k = " << k << ": \nx = " << NewtonMethod(epsilon, k, n)
                      << "\nКоличество итераций: " << n << std::endl;
            break;
        case Task::HalfDivision:
            double xLeft = 0;
            double xRight = 0;

            std::cout << "Введите левую границу и правую через пробел в формате {xLeft xRight}: ";
            std::cin >> xLeft >> xRight;

            std::cout << "Результат метода половинного деления, ε = " << epsilon << ", k = " << k
                      << ": \nx = " << HalfDivision(epsilon, k, n, xLeft, xRight) << "\nКоличество итераций: " << n << std::endl;
            break;
    }
}
}  // namespace task
