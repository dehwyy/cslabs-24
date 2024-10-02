#include <cmath>
#include <iomanip>
#include <iostream>

void Task1() {
    int n = 0;
    int m = 0;
    std::cout << "Enter n and m in format {n m}. \x1b[1;31mNOTE! n > m, n > 1\x1b[0m: ";
    std::cin >> n >> m;

    if (n < 1) {
        std::cout << "n must be > 1\n";
        return;
    }

    if (m >= n) {
        std::cout << "m must be < n\n";
        return;
    }

    int sum = 0;
    for (int i = 5; i <= n; i += 5) {
        if (i % m != 0)
            sum += i;
    }
    std::cout << "\x1b[1;34mSum of natural numbers in range [1, " << n << "] = " << sum << "\x1b[0m\n";
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

    std::cout << "\x1b[1;35mS = " << sum << "\x1b[0m\n";
}

float Task3CalculateSxMember(float x, int n) {
    return pow(x, 2 * n + 1) / (2 * n + 1);
}

void Task3() {
    std::cout << " x         Y(x)            S(x)              N\n";

    std::cout << std::setprecision(6);
    for (float x = 0; x <= 1; x += 0.2) {
        float s = 0;
        float sTaylorKoef = Task3CalculateSxMember(x, 2) / Task3CalculateSxMember(x, 1);
        float lastTaylorSequenceMember = Task3CalculateSxMember(x, 1);

        while (lastTaylorSequenceMember > 1e-6) {
            s += lastTaylorSequenceMember;
            lastTaylorSequenceMember *= sTaylorKoef;
        }

        float y = log((1 - x) / (1 + x));

        std::cout << std::setw(3) << x << "\t";
        std::cout << std::setw(9) << y << "\t";
        std::cout << std::setw(9) << s << "\t";
        std::cout << std::setw(11) << lastTaylorSequenceMember << "\n";
    }
}

float Task4CalculateMember(float x, int n) {
    return pow(x, n + 1) / (n * pow(2, n));
}

void Task4() {

    float x = 0;
    std::cout << "Enter x: ";
    std::cin >> x;

    while (true) {
        int n = 0;
        std::cout << "Enter n (enter 0 to exit): ";
        std::cin >> n;
        if (n == 0) {
            break;
        }

        float y = 0;
        float yTaylorKoef = Task4CalculateMember(x, 2) / Task4CalculateMember(x, 1);
        float lastTaylorSequenceMember = Task4CalculateMember(x, 1);

        for (int i = 1; i < n + 1; ++i) {
            y += lastTaylorSequenceMember;
            lastTaylorSequenceMember *= yTaylorKoef;
            if (i == 3 || i == 5 || i == 10) {
                std::cout << "Partial sum for first " << i << " members = " << y << "\n";
            }
        }

        std::cout << "y = " << y << "\n";
    }

}

int AppStart() {
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
            Task4();
            break;
        default:
            return 1;
    }

    std::cout << "\n";

    return 0;
}

int main(int, char**) {
    while (true) {
        if (AppStart() != 0) {
            std::cout << "Goodbye!\n";
            break;
        }
    }
    return 0;
}
