#pragma once

#include "app.h"

namespace args_parser {
struct Args {
    app::Mode mode = app::Mode::Interactive;
};

Args Parse(int argc, char* argv[]);
}  // namespace args_parser
