#include "rsa.h"
#include <cmath>
#include <iostream>

namespace {
long power(long base, long exp, long mod) {
    long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp = exp >> 1;  // Делим exp на 2
    }
    return result;
}

int GetD(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }

    return -1;
}

int GetN(int p, int q) {
    return p * q;
}

int GetPhi(int p, int q) {
    return (p - 1) * (q - 1);
}

int GetGreatestCommonDivisor(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }

    return a;
}

int GetE(int phi) {
    int e = 3;
    while (GetGreatestCommonDivisor(e, phi) != 1) {
        e += 2;
    }

    return e;
}

}  // namespace

namespace rsa {
long Encode(long message, long e, long n) {
    return power(message, e, n);
}

long Decode(long message, long d, long n) {
    return power(message, d, n);
}

void RunExample() {
    const int p = 19;
    const int q = 41;

    const int n = GetN(p, q);
    const int phi = GetPhi(p, q);
    const int e = GetE(phi);
    const int d = GetD(e, phi);

    const int message = 727;

    std::cout << "Открытый ключ: " << e << " " << n << std::endl;
    std::cout << "Приватный ключ: " << d << " " << n << std::endl;

    std::cout << "Число для шифрования: " << message << std::endl;

    long encoded = Encode(message, e, n);
    long decoded = Decode(encoded, d, n);

    std::cout << "Зашифрованное сообщение: " << encoded << std::endl;
    std::cout << "Расшифрованное сообщение: " << decoded << std::endl;
}

void RunTask() {
    const int e = 53;
    const int n = 299;
    const long encoded_message = 171;

    // подобранные простые числа p и q для N = 299
    const int p = 13;
    const int q = 23;

    const int phi = GetPhi(p, q);
    const int d = GetD(e, phi);
    long decoded = Decode(encoded_message, d, n);

    std::cout << "Число для расшифровки: " << encoded_message << std::endl;
    std::cout << "Приватный ключ: " << d << " " << n << std::endl;
    std::cout << "Расшифрованное сообщение: " << decoded << std::endl;
}
}  // namespace rsa
