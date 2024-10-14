#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
const int kTaskNumberMin = 1;
const int kTaskNumberMax = 4;

const int kTask1ModBase = 5;

const int kTask2Case1Min = 2;
const int kTask2Case1Max = 8;
const int kTask2Case1Step = 2;
const int kTask2Case2Min = 3;
const int kTask2Case2Max = 9;
const int kTask2Case2Step = 3;

const float kTask3XStep = 0.2;
const int kTask3TableColumnWidth = 16;
const int kEpsilonPrecision = 6;
const double kEpsilon = 1e-6;

const int kTask4CalculateN1 = 3;
const int kTask4CalculateN2 = 5;
const int kTask4CalculateN3 = 10;

const char* const kOutputStyleRed = "\x1b[1;31m";
const char* const kOutputStyleGreen = "\x1b[1;32m";
const char* const kOutputStyleBlue = "\x1b[1;34m";
const char* const kOutputStyleMagenta = "\x1b[1;35m";
const char* const kOutputStyleReset = "\x1b[0m";
}  // namespace

void Task1PrintUsage() {
    std::cout << "Введите 'n' и 'm' в формате: {n m}. ";
}

void Task1() {
    std::cout << kOutputStyleGreen << "Задание 1. Сумма натуральных чисел на отрезке от [1 до `n`], которые делятся на 5 и не делятся на `m`.\n"
              << kOutputStyleReset;

    int n = 0;
    int m = 0;

    Task1PrintUsage();
    std::cout << kOutputStyleRed << "ЗАМЕЧАНИЕ! n > m, n > 1, m != 0: " << kOutputStyleReset;
    std::cin >> n >> m;

    while (n < 1 || m >= n || m == 0) {
        if (n < 1) {
            std::cout << kOutputStyleRed << "n должно быть > 1!\n" << kOutputStyleReset;
        }

        if (m >= n) {
            std::cout << kOutputStyleRed << "m должно быть < n!\n" << kOutputStyleReset;
        }

        if (m == 0) {
            std::cout << kOutputStyleRed << "m не может быть 0!\n" << kOutputStyleReset;
        }

        Task1PrintUsage();
        std::cin >> n >> m;
    }

    int sum = 0;
    for (int i = 0; i <= n; i += kTask1ModBase) {
        if (i % m != 0) {
            sum += i;
        }
    }

    std::cout << kOutputStyleBlue << "Сумма чисел в диапазоне [1, " << n << "], которые соответствуют условию = " << sum << kOutputStyleReset << "\n";
}

void Task2() {
    std::cout << kOutputStyleGreen << "Задание 2.\n"
              << "Произведение от 2 до 8 с шагом i=2 членов (i^2 - a), если a >= =0.\n"
              << "Произведение от 3 до 9 с шагом i=3 членов (i - 2)  , если a < 0.\n"
              << kOutputStyleReset;

    double a = 0;
    std::cout << "Введите a: ";
    std::cin >> a;

    double s = 1;
    if (a >= 0) {
        for (int i = kTask2Case1Min; i <= kTask2Case1Max; i += kTask2Case1Step) {
            s *= std::pow(i, 2) - a;
        }
    } else {
        for (int i = kTask2Case2Min; i <= kTask2Case2Max; i += kTask2Case2Step) {
            s *= i - 2;
        }
    }

    std::cout << kOutputStyleMagenta << "S = " << s << kOutputStyleReset << "\n";
}

double Task3CalculateSeriesMember(float x, int n) {
    return std::pow(x, 2 * n + 1) / (2 * n + 1);
}

void Task3() {
    std::cout << kOutputStyleGreen << "Задание 3. Вычисление значений ряда S(x) и функции Y(x).\n\n" << kOutputStyleReset;

    std::cout << std::left << std::setprecision(kEpsilonPrecision);
    std::cout << std::setw(kTask3TableColumnWidth) << "x" << std::setw(kTask3TableColumnWidth) << "Y(x)" << std::setw(kTask3TableColumnWidth)
              << "S(x)" << std::setw(kTask3TableColumnWidth) << "N" << "\n\n";

    for (float x = 0; x <= 1.; x += kTask3XStep) {
        double s = 0;
        int n = 0;
        double currentSeriesMember = Task3CalculateSeriesMember(x, n);

        while (std::fabs(currentSeriesMember) > kEpsilon) {
            s += currentSeriesMember;

            currentSeriesMember = Task3CalculateSeriesMember(x, ++n);
        }

        double y = std::log((1 + x) / (1 - x));

        std::cout << std::setw(kTask3TableColumnWidth) << x;
        std::cout << std::setw(kTask3TableColumnWidth) << y;
        std::cout << std::setw(kTask3TableColumnWidth) << 2 * s;
        std::cout << std::setw(kTask3TableColumnWidth) << n << "\n";
    }
}

double Task4CalculateSeriesMember(double x, int n) {
    return std::pow(x, n + 1) / (n * std::pow(2, n));
}

void Task4() {
    std::cout << kOutputStyleGreen << "Вычисление суммы первых n-членов y по формуле: y = x + (x^2) / (1*2) + ... + (x^(n+1)) / (n*2^n).\n" << kOutputStyleReset;

    double x = 0;
    std::cout << "Введите x (float): ";
    std::cin >> x;

    int n = 0;
    std::cout << "Введите n (натуральное): ";
    std::cin >> n;

    while (n < 1) {
        std::cout << "'n' должно быть натуральным! Введите 'n' еще раз: ";
        std::cin >> n;
    }

    std::cout << std::fixed;

    double y = x;
    int currentSeriesMemberNumber = 1;
    double currentSeriesMember = Task4CalculateSeriesMember(x, currentSeriesMemberNumber);

    while (currentSeriesMemberNumber < n) {
        y += currentSeriesMember;

        currentSeriesMember = Task4CalculateSeriesMember(x, ++currentSeriesMemberNumber);

        if (currentSeriesMemberNumber == kTask4CalculateN1 || currentSeriesMemberNumber == kTask4CalculateN2 ||
            currentSeriesMemberNumber == kTask4CalculateN3) {
            std::cout << "Частичная сумма для первых " << currentSeriesMemberNumber << " членов = " << y << "\n";
        }
    }

    std::cout << kOutputStyleBlue << "y = " << y << kOutputStyleReset << "\n";
}

int main(int, char**) {
    char continueAnswer = 'y';

    while (continueAnswer == 'y' || continueAnswer == 'Y') {
        std::cout << "Введите номер задания для исполнения: [1, 2, 3, 4]: ";

        int taskNumber = 0;
        std::cin >> taskNumber;

        while (taskNumber < kTaskNumberMin || taskNumber > kTaskNumberMax) {
            std::cout << "Неверный номер задания! Возможные номера: [1, 2, 3, 4]: ";
            std::cin >> taskNumber;
        }

        switch (taskNumber) {
            case 1:
                Task1();
                break;
            case 2:
                Task2();
                break;
            case 3:
                Task3();
                break;
            case 4:
                Task4();
                break;
        }

        std::cout << "\n";

        std::cout << kOutputStyleGreen << "Продолжить? (y/n): " << kOutputStyleReset;
        std::cin >> continueAnswer;
    }

    std::cout << kOutputStyleMagenta << "До свидания!" << kOutputStyleReset << "\n";

    return 0;
}
