#include <iostream>
#include "src/app.h"
#include "src/args_parser.h"
#include "src/caeser_cypher.h"
#include "src/internal/fs.h"
#include "src/internal/str.h"
#include "src/internal/vec.h"

namespace {
const int WORD_LEN = 10;
}

void t();

int main(int argc, char** argv) {
    auto args = args_parser::parse(argc, argv);
    std::cout << "Args: " << args << std::endl;

    app::Run(t);
    return 0;
}

void t() {
    fs::File file_cypher(str::String("zcypher.txt"));
    fs::File file(str::String("ztext.txt"));
    fs::File writefile(str::String("output.txt"));

    auto buf = vec::Vec<str::String>();
    file.ReadAll(buf, WORD_LEN);

    auto buf2 = vec::Vec<str::String>();
    file_cypher.ReadAll(buf2, WORD_LEN);

    std::cout << "Cypher: " << buf2 << std::endl;
    auto cyph = caeser_cypher::CypherWords(buf2);

    auto buf3 = vec::Vec<str::String>();
    for (size_t i = 0; i < buf.len(); ++i) {
        auto temp = vec::Vec<char>();
        caeser_cypher::encode(buf.get(i), temp, cyph);
        buf3.push(str::String(temp));
    }

    std::cout << "Encoded: " << buf3 << std::endl;

    writefile.WriteAll(buf3);

    fs::File fileencoded(str::String("output.txt"));
    fs::File filedecoded(str::String("output2.txt"));

    auto buf4 = vec::Vec<str::String>();
    fileencoded.ReadAll(buf4, WORD_LEN, true);

    auto buf5 = vec::Vec<str::String>();
    for (size_t i = 0; i < buf4.len(); ++i) {
        auto temp = vec::Vec<char>();
        caeser_cypher::decode(buf4.get(i), temp, cyph);
        buf5.push(str::String(temp));
    }

    std::cout << "Decoded: " << buf5 << std::endl;

    filedecoded.WriteAll(buf5);
}
