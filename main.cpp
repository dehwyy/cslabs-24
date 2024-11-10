#include <iostream>
#include "src/app.h"

int main(int argc, char** argv) {
    auto args = args_parser::parse(argc, argv);
    app::Run(args);
    return 0;
}
