#include "app.h"
#include <iostream>
#include "internal/rsa.h"

namespace app {

void Run() {
    std::cout << "Пример:" << std::endl;
    rsa::RunExample();
    std::cout << std::endl;

    std::cout << "Задание:" << std::endl;
    rsa::RunTask();
    std::cout << std::endl;

    char input = 'y';
    while (input == 'y') {
        std::cout << "Интерактивный режим:" << std::endl;
        rsa::RunInteractive();
        std::cout << std::endl;
        std::cout << "Продолжить?(y/n): ";
        std::cin >> input;
    }
}
}  // namespace app
