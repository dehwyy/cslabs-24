#include "app.h"
#include <iostream>

namespace app {

void Run(Mode mode) {
    std::cout << "Mode: " << static_cast<int>(mode) << std::endl;
}
}  // namespace app
