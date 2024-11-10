#include "collections/str.h"
#include "collections/vec.h"

namespace args_parser {
struct ParsedFilenames {
    str::String input_file;
    str::String cypher_file;
    str::String encoded_output_file;
    str::String decoded_output_file;

    bool is_filled();
};

ParsedFilenames parse(int argc, char** argv);
void PrintHelp();
}  // namespace args_parser
