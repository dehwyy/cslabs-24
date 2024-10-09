#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
const int kTask1RangeSumStep = 5;

const int kTask2Case1Min = 2;
const int kTask2Case1Max = 8;
const int kTask2Case1Step = 2;
const int kTask2Case2Min = 3;
const int kTask2Case2Max = 9;
const int kTask2Case2Step = 3;

const float kTask3XStep = 0.2;
const int kTask3TableOffset = 16;
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
    std::cout << "Enter n and m in format {n m}: ";
}

void Task1() {
    int n = 0;
    int m = 0;

    Task1PrintUsage();
    std::cout << kOutputStyleRed << "NOTE! n > m, n > 1: " << kOutputStyleReset;
    std::cin >> n >> m;

    while (n < 1 || m >= n) {
        if (n < 1) {
            std::cout << kOutputStyleRed << "n must be > 1!\n" << kOutputStyleReset;
        }

        if (m >= n) {
            std::cout << kOutputStyleRed << "m must be < n!\n" << kOutputStyleReset;
        }

        Task1PrintUsage();
        std::cin >> n >> m;
    }

    int sum = 0;
    for (int i = 0; i <= n; i += kTask1RangeSumStep) {
        if (i % m != 0) {
            sum += i;
        }
    }
    std::cout << kOutputStyleBlue << "Sum of natural numbers in range [1, " << n << "], which match the condition = " << sum << kOutputStyleReset
              << "\n";
}

void Task2() {
    double a = 0;
    std::cout << "Enter a: ";
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
    std::cout << std::left << std::setprecision(kEpsilonPrecision);
    std::cout << std::setw(kTask3TableOffset) << "x" << std::setw(kTask3TableOffset) << "Y(x)" << std::setw(kTask3TableOffset) << "S(x)"
              << std::setw(kTask3TableOffset) << "N" << "\n\n";

    for (float x = 0; x <= 1.; x += kTask3XStep) {
        double s = 0;
        int currentSeriesMemberNumber = 0;
        double currentSeriesMember = Task3CalculateSeriesMember(x, currentSeriesMemberNumber);

        while (std::fabs(currentSeriesMember) > kEpsilon) {
            s += currentSeriesMember;

            currentSeriesMember = Task3CalculateSeriesMember(x, ++currentSeriesMemberNumber);
        }

        double y = log((1 + x) / (1 - x));

        std::cout << std::setw(kTask3TableOffset) << x;
        std::cout << std::setw(kTask3TableOffset) << y;
        std::cout << std::setw(kTask3TableOffset) << 2 * s;
        std::cout << std::setw(kTask3TableOffset) << currentSeriesMemberNumber << "\n";
    }
}

double Task4CalculateSeriesMember(double x, int n) {
    return pow(x, n + 1) / (n * pow(2, n));
}

void Task4() {
    double x = 0;
    std::cout << "Enter x (float): ";
    std::cin >> x;

    int n = 0;
    std::cout << "Enter n (natural): ";
    std::cin >> n;

    while (n < 1) {
        std::cout << "N should be natural! Enter n (natural): ";
        std::cin >> n;
    }

    double y = 0;
    double yTaylorKoef = Task4CalculateSeriesMember(x, 2) / Task4CalculateSeriesMember(x, 1);
    double lastTaylorSequenceMember = Task4CalculateSeriesMember(x, 1);

    for (int i = 1; i < n + 1; ++i) {
        y += lastTaylorSequenceMember;
        lastTaylorSequenceMember *= yTaylorKoef;
        if (i == kTask4CalculateN1 || i == kTask4CalculateN2 || i == kTask4CalculateN3) {
            std::cout << "Partial sum for first " << i << " members = " << y << "\n";
        }
    }

    std::cout << "y = " << y << "\n";
}

int AppStart() {
    std::cout << "Select a task to run! The task may be [1, 2, 3, 4]: ";

    int task = 0;
    std::cin >> task;

    while (task < 1 || task > 4) {
        std::cout << "Incorrect task number! The task may be [1, 2, 3, 4]: ";
        std::cin >> task;
    }

    switch (task) {
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
        default:
            return 1;
    }

    std::cout << "\n";

    return 0;
}

int main(int, char**) {
    char continueAnswer = 'y';

    while (continueAnswer == 'y' || continueAnswer == 'Y') {
        AppStart();

        std::cout << kOutputStyleGreen << "Continue? (y/n): " << kOutputStyleReset;
        std::cin >> continueAnswer;
    }

    std::cout << kOutputStyleMagenta << "Goodbye!" << kOutputStyleReset << "\n";

    return 0;
}
