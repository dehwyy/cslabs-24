#include "src/app.h"
#include "src/args_parser.h"

int main(int argc, char** argv) {
    auto args = args_parser::Parse(argc, argv);
    app::Run(args.mode);
    return 0;
}
