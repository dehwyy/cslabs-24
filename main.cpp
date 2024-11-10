#include <iostream>
#include "src/app.h"
#include "src/args_parser.h"
#include "src/caeser_cypher.h"
#include "src/collections/str.h"
#include "src/collections/vec.h"
#include "src/lib/fs.h"

namespace {
const int WORD_LEN = 5;
}

void t();

int main(int argc, char** argv) {
    std::cout << "\n__APP__\n" << std::endl;
    auto args = args_parser::parse(argc, argv);
    std::cout << "Args: " << args << std::endl;

    app::Run(t);

    return 0;
}

void t() {
    auto dataf = fs::ReadAllVec(str::String("ztext.txt"), WORD_LEN);

    std::cout << "dataf: " << dataf << std::endl;

    auto data = vec::Vec<str::String>();
    for (size_t i = 0; i < dataf.len(); ++i) {
        data.extend(str::Split(dataf.get(i)));
    }

    std::cout << "Data: " << data << std::endl;

    auto joined_data = str::Joined(data);
    std::cout << "Joined data: " << joined_data << std::endl;

    auto grouped_data = str::GroupedBy(joined_data, WORD_LEN);

    std::cout << "Grouped by 5" << grouped_data << std::endl;

    auto cypher_data = fs::ReadAllVec(str::String("zcypher.txt"), WORD_LEN);
    std::cout << "cypher_data: " << cypher_data << std::endl;

    auto processed_cypher_data = vec::Vec<str::String>();
    for (size_t i = 0; i < cypher_data.len(); ++i) {
        auto v = str::Split(cypher_data.get(i));
        processed_cypher_data.push(str::Joined(v));
    }

    std::cout << "processed_cypher_data: " << processed_cypher_data << std::endl;

    auto cypher_words = caeser_cypher::CypherWords(processed_cypher_data);

    auto encoded_data = vec::Vec<str::String>();
    for (size_t i = 0; i < grouped_data.len(); ++i) {
        auto encoded_s = caeser_cypher::encode(grouped_data.get(i), cypher_words);
        encoded_data.push(encoded_s);
    }

    std::cout << "Encoded: " << encoded_data << std::endl;
    fs::WriteAllVec(str::String("output.txt"), encoded_data);

    // auto encodedf_data = vec::Vec<str::String>();
    auto encodedf_data = fs::ReadAllVec(str::String("output.txt"), WORD_LEN);

    std::cout << "encodedf_data: " << encodedf_data << std::endl;

    auto decoded_data = vec::Vec<str::String>();
    for (size_t i = 0; i < encodedf_data.len(); ++i) {
        auto decoded_s = caeser_cypher::decode(encodedf_data.get(i), cypher_words);
        decoded_data.push(decoded_s);
    }
    fs::WriteAllVec(str::String("output2.txt"), decoded_data);

    std::cout << "Decodedd: " << decoded_data << std::endl;
    std::cout << "\n__END__\n" << std::endl;
}
