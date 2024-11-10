#include "args_parser.h"

namespace {
const str::String ARGS_PREFIX("--");
const str::String ARGS_DELIMETER("=");

const str::String INPUT_FILE("file");
const str::String CYPHER_FILE("cypher");
const str::String ENCODED_OUTPUT_FILE("encoded");
const str::String DECODED_OUTPUT_FILE("decoded");
}  // namespace

namespace args_parser {
bool ParsedFilenames::is_filled() {
    return input_file.len() && cypher_file.len() && encoded_output_file.len() && decoded_output_file.len();
}

ParsedFilenames parse(int argc, char** argv) {
    auto args = ParsedFilenames{};

    for (int i = 1; i < argc; i++) {
        auto s = str::String(argv[i]);

        if (!str::StartsWith(s, ARGS_PREFIX)) {
            continue;
        }

        s = str::Slice(s, ARGS_PREFIX.len());

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
}  // namespace args_parser
