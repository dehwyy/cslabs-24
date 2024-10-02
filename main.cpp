#include <cmath>
#include <iomanip>
#include <iostream>

void Task1() {
    int n = 0;
    int m = 0;
    std::cout << "Enter n and m in format {n m}. NOTE! m < n: ";
    std::cin >> n >> m;

    int sum = 0;
    for (int i = 5; i <= n; i += 5) {
        if (i % m != 0)
            sum += i;
    }
    std::cout << "Sum of natural numbers in range [1, " << n << "] = " << sum << "\n";
}

void Task2() {
    int a = 0;
    std::cout << "Enter a: ";
    std::cin >> a;

    int sum = 1;
    if (a >= 0) {
        for (int i = 2; i <= 8; i += 2) {
            sum *= pow(i, 2) - a;
        }
    } else {
        for (int i = 3; i <= 9; i += 3) {
            sum *= i - 2;
        }
    }

    std::cout << "S = " << sum << "\n";
}

float Task3SxMember(float x, int n) {
    return pow(x, 2 * n + 1) / (2 * n + 1);
}

void Task3() {
    std::cout << "x\tY(x)\tS(x)\tN\n";
    for (float x = 0; x <= 1; x += 0.2) {
        float s = 0;
        float sTaylorKoef = Task3SxMember(x, 2) / Task3SxMember(x, 1);
        float lastTaylorSequenceMember = Task3SxMember(x, 1);

        do {
            s += lastTaylorSequenceMember;
            lastTaylorSequenceMember *= sTaylorKoef;
        } while (lastTaylorSequenceMember < 1e-6);

        float y = log((1 - x) / (1 + x));

        std::cout << std::setw(3) << x << "\t";

        std::cout << std::setw(7) << y << "\t" << s << "\t" << lastTaylorSequenceMember << "\n";
    }
}

void AppStart() {
    std::cout << "Select a task to run! The task may be [1, 2, 3, 4]: ";

    int task = 0;
    std::cin >> task;

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
            break;
        default:
            break;
    }
}

int main(int, char**) {
    AppStart();
    return 0;
}
