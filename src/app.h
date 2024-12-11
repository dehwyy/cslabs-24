#pragma once
#include <iostream>
#include "args_parser.h"
#include "caeser_cipher.h"
#include "collections/str.h"
#include "collections/vec.h"
#include "lib/fs.h"

namespace app {
void Run(args_parser::ParsedFilenames filenames);
}  // namespace app
