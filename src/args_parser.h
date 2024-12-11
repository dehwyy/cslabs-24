#include "collections/vec.h"

namespace args_parser {
struct ParsedFilenames {
    char* source_file;
    char* cipher_file;
    char* encoded_output_file;
    char* decoded_output_file;
};

ParsedFilenames Parse(int argc, char** argv);
bool IsFilledStruct(ParsedFilenames filenames);
void PrintHelp();
}  // namespace args_parser
