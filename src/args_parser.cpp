#include "args_parser.h"

namespace args_parser {
vec::Vec<str::String> parse(int argc, char** argv) {
    vec::Vec<str::String> args;

    for (int i = 1; i < argc; i++) {
        args.push(str::String(argv[i]));
    }

    return args;
}
}  // namespace args_parser
