#include "args_parser.h"
#include "cstring"

namespace args_parser {

Args Parse(int argc, char* argv[]) {
    auto args = Args{.mode = app::Mode::Interactive};

    for (int i = 1; i < argc; i++) {
        if (std::strcmp(argv[i], "--demo") == 0) {
            args.mode = app::Mode::Demonstration;
        } else if (std::strcmp(argv[i], "--i") == 0) {
            args.mode = app::Mode::Interactive;
        }
    }

    return args;
}
}  // namespace args_parser
