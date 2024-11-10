#include <iostream>
#include "src/app.h"

// --file=ztext.txt --cypher=zcypher.txt --encoded=output.txt --decoded=output2.txt

int main(int argc, char** argv) {
    std::cout << "\n__APP__\n" << std::endl;
    auto args = args_parser::parse(argc, argv);

    if (!args.is_filled()) {
        std::cerr << "Failed to parse args!" << std::endl;
        return 1;
    }

    std::cout << "Input file: " << args.input_file << std::endl;
    std::cout << "Cypher file: " << args.cypher_file << std::endl;
    std::cout << "Encoded output file: " << args.encoded_output_file << std::endl;
    std::cout << "Decoded output file: " << args.decoded_output_file << std::endl;

    app::Run(app::RunCaesarCypher, args);

    return 0;
}
