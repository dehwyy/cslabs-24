#pragma once
#include <iostream>
#include "args_parser.h"
#include "caeser_cypher.h"
#include "collections/str.h"
#include "collections/vec.h"
#include "lib/fs.h"

namespace app {
void Run(void (*execute)(args_parser::ParsedFilenames filenames), args_parser::ParsedFilenames filenames);
void RunCaesarCypher(args_parser::ParsedFilenames filenames);
}  // namespace app
