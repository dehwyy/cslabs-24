#include "collections/str.h"
#include "collections/vec.h"

namespace args_parser {
struct ParsedFilenames {
    str::String input_file;
    str::String cipher_file;
    str::String encoded_output_file;
    str::String decoded_output_file;
};

ParsedFilenames parse(int argc, char** argv);
bool IsFilledStruct(ParsedFilenames filenames);
void PrintHelp();
}  // namespace args_parser
