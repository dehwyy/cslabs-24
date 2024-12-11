#include <iostream>
#include "args_parser.h"
#include "caeser_cipher.h"
#include "lib/fs.h"

namespace App {

void Run(int argc, char** argv) {
    args_parser::ParsedFilenames args = args_parser::Parse(argc, argv);

    const char* source = fs::ReadFile(args.source_file);
    const char* keys = fs::ReadFile(args.cipher_file);

    vec::VecInt processedKeys = CaesarCipher::CreateNotebookKeys(keys);

    const char* encode = CaesarCipher::Encode(source, processedKeys);
    const char* decode = CaesarCipher::Decode(encode, processedKeys);

    fs::WriteFile(args.encoded_output_file, encode);
    fs::WriteFile(args.decoded_output_file, decode);

    CaesarCipher::GenerateStatistics(source, encode, processedKeys);
}

}  // namespace App
