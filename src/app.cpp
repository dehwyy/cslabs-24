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
}
}  // namespace app
