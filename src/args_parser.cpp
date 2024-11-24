#include "args_parser.h"
#include <iostream>
namespace {
const str::String ARGS_PREFIX = str::FromStaticCStr("--");
const str::String ARGS_DELIMETER = str::FromStaticCStr("=");

const str::String INPUT_FILE = str::FromStaticCStr("file");
const str::String CYPHER_FILE = str::FromStaticCStr("cypher");
const str::String ENCODED_OUTPUT_FILE = str::FromStaticCStr("encoded");
const str::String DECODED_OUTPUT_FILE = str::FromStaticCStr("decoded");
}  // namespace

namespace args_parser {
bool IsFilledStruct(ParsedFilenames f) {
    return str::Len(f.input_file) && str::Len(f.cypher_file) && str::Len(f.encoded_output_file) && str::Len(f.decoded_output_file);
}

ParsedFilenames parse(int argc, char** argv) {
    auto args = ParsedFilenames{};

    for (int i = 1; i < argc; i++) {
        auto s = str::FromCStr(argv[i]);

        if (!str::StartsWith(s, ARGS_PREFIX)) {
            continue;
        }

        s = str::Slice(s, str::Len(ARGS_PREFIX));

        auto parts = str::Split(s, ARGS_DELIMETER);

        auto key = parts.get(0);
        auto value = parts.get(1);

        if (str::Equals(key, INPUT_FILE)) {
            args.input_file = value;
        } else if (str::Equals(key, CYPHER_FILE)) {
            args.cypher_file = value;
        } else if (str::Equals(key, ENCODED_OUTPUT_FILE)) {
            args.encoded_output_file = value;
        } else if (str::Equals(key, DECODED_OUTPUT_FILE)) {
            args.decoded_output_file = value;
        };
    }

    return args;
}

void PrintHelp() {
    std::cout << "\nUsage: ./[bin] [FILES]\n" << std::endl;
    std::cout << "Files:" << std::endl;
    std::cout << " --file=<path> - path to input file" << std::endl;
    std::cout << " --cypher=<path> - path to cypher file" << std::endl;
    std::cout << " --encoded=<path> - path to encoded output file" << std::endl;
    std::cout << " --decoded=<path> - path to decoded output file" << std::endl;
}

}  // namespace args_parser
