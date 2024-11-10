#include "app.h"

namespace {
const int WORD_LEN = 5;

vec::Vec<str::String> Encode(const vec::Vec<str::String>& data, caeser_cypher::CypherWords& cypher_words) {
    auto encoded_data = vec::Vec<str::String>();
    for (size_t i = 0; i < data.len(); ++i) {
        auto encoded_s = caeser_cypher::encode(data.get(i), cypher_words);
        encoded_data.push(encoded_s);
    }

    return encoded_data;
}

vec::Vec<str::String> Decode(const vec::Vec<str::String>& data, caeser_cypher::CypherWords& cypher_words) {
    auto decoded_data = vec::Vec<str::String>();
    for (size_t i = 0; i < data.len(); ++i) {
        auto decoded_s = caeser_cypher::decode(data.get(i), cypher_words);
        decoded_data.push(decoded_s);
    }

    return decoded_data;
}

}  // namespace

namespace app {
void Run(void (*execute)(args_parser::ParsedFilenames filenames), args_parser::ParsedFilenames filenames) {
    char input = 'y';

    while (input == 'y') {
        execute(filenames);

        std::cout << "Продолжить выполнение? (y/n): ";
        std::cin >> input;
    }
}

void RunCaesarCypher(args_parser::ParsedFilenames filenames) {
    auto cypher_file_data = fs::ReadAllVec(filenames.cypher_file, WORD_LEN);
    auto cypher_words = caeser_cypher::CypherWords(cypher_file_data);

    auto input_file_data = fs::ReadAllVec(filenames.input_file, WORD_LEN);
    auto input_data_as_str = str::Joined(input_file_data);
    auto input_data = str::GroupedBy(input_data_as_str, WORD_LEN);

    auto encoded_data = Encode(input_data, cypher_words);
    fs::WriteAllVec(filenames.encoded_output_file, encoded_data);

    auto decoded_data = Decode(encoded_data, cypher_words);
    fs::WriteAllVec(filenames.decoded_output_file, decoded_data);
}
}  // namespace app
