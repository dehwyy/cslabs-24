#include "args_parser.h"
#include <cstring>
#include <iostream>

namespace {
const char* SOURCE_FILE = "--file=";
const char* CIPHER_FILE = "--cipher=";
const char* ENCODED_OUTPUT_FILE = "--encoded=";
const char* DECODED_OUTPUT_FILE = "--decoded=";

bool StartsWith(const char* str, const char* prefix) {
    return std::strncmp(str, prefix, std::strlen(prefix)) == 0;
}

}  // namespace

namespace args_parser {
bool IsFilledStruct(ParsedFilenames f) {
    return f.source_file && f.cipher_file && f.encoded_output_file && f.decoded_output_file;
}

ParsedFilenames Parse(int argc, char** argv) {
    auto args = ParsedFilenames{};

    for (int i = 1; i < argc; i++) {
        char* s = argv[i];

        if (StartsWith(s, SOURCE_FILE)) {
            args.source_file = argv[i] + std::strlen(SOURCE_FILE);
        } else if (StartsWith(s, CIPHER_FILE)) {
            args.cipher_file = argv[i] + std::strlen(CIPHER_FILE);
        } else if (StartsWith(s, ENCODED_OUTPUT_FILE)) {
            args.encoded_output_file = argv[i] + std::strlen(ENCODED_OUTPUT_FILE);
        } else if (StartsWith(s, DECODED_OUTPUT_FILE)) {
            args.decoded_output_file = argv[i] + std::strlen(DECODED_OUTPUT_FILE);
        };
    }

    return args;
}

void PrintHelp() {
    std::cout << "\nUsage: ./[bin] [FILES]\n" << std::endl;
    std::cout << "Files:" << std::endl;
    std::cout << " --file=<path> - path to input file" << std::endl;
    std::cout << " --cipher=<path> - path to cipher file" << std::endl;
    std::cout << " --encoded=<path> - path to encoded output file" << std::endl;
    std::cout << " --decoded=<path> - path to decoded output file" << std::endl;
}

}  // namespace args_parser
