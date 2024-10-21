#include <iostream>

namespace app {
  void Run(void (* execute)()) {
    char input = 'y';

    while (input == 'y') {
      execute();

      std::cout << "Продолжить выполнение? (y/n): ";
      std::cin >> input;
    }
  }
}
