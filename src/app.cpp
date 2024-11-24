#include "app.h"

namespace {
const char DEFAULT_CHAR_PRINT = 'z';
const char DEFAULT_CHAR_PRINT_NEIGHBOURS = 2;

const char* const ANSI_CLEAR_SCREEN = "\x1B[2J\x1B[H";

const char ANSI_MIN_CHAR = 0;
const char ANSI_MAX_CHAR = 127;

const int WORD_LEN = 300;
const int CYPHER_LEN = 100;

bool IsValidAnsi(int ch) {
    return ch >= ANSI_MIN_CHAR && ch <= ANSI_MAX_CHAR;
}

void PrintChar(char ch, const caeser_cypher::SymbolCypherStats& stats) {
    std::cout << "Символ: '" << ch << "'" << std::endl;
    std::cout << "-Код символа ANSI: " << static_cast<int>(ch) << std::endl;
    std::cout << "-Вхождение в исходный текст: " << stats.total << std::endl;
    std::cout << "-Различных вариантов шифрования: " << stats.different_encodes.len() << std::endl << std::endl;
}

void PrintStatistics(const caeser_cypher::TotalCypherStats& stats) {
    int ch = DEFAULT_CHAR_PRINT;

    while (ch >= ANSI_MIN_CHAR && ch <= ANSI_MAX_CHAR) {
        std::cout << ANSI_CLEAR_SCREEN;
        std::cout << "Длина исходного текста: " << stats.input_text_len << std::endl;
        std::cout << "Количество слов в блокноте шифрования: " << stats.cypher_notebook_len << std::endl << std::endl;

        auto chars_to_print = vec::Vec<char>();

        char printed_neighbours = 0;
        int shift = -1;
        while (printed_neighbours < DEFAULT_CHAR_PRINT_NEIGHBOURS) {
            int new_ch = ch + shift;
            if (!IsValidAnsi(new_ch)) {
                break;
            }

            if (stats.symbols[new_ch].total) {
                ++printed_neighbours;
                chars_to_print.push(static_cast<char>(new_ch));
            }

            --shift;
        }

        chars_to_print.reverse();
        chars_to_print.push(static_cast<char>(ch));

        printed_neighbours = 0;
        shift = 1;
        while (printed_neighbours < DEFAULT_CHAR_PRINT_NEIGHBOURS) {
            int new_ch = ch + shift;
            if (!IsValidAnsi(new_ch)) {
                break;
            }

            if (stats.symbols[new_ch].total) {
                ++printed_neighbours;
                chars_to_print.push(static_cast<char>(new_ch));
            }

            ++shift;
        }

        for (size_t i = 0; i < chars_to_print.len(); ++i) {
            char ch = chars_to_print.get(i);
            PrintChar(ch, stats.symbols[static_cast<size_t>(ch)]);
        }

        std::cout << "\nВведите код символа ANSI для просмотра статистики или -1 для выхода: ";
        std::cin >> ch;
    }
}

vec::Vec<str::String> Encode(const vec::Vec<str::String>& data, caeser_cypher::CypherWords& cypher_words, caeser_cypher::TotalCypherStats& stats) {
    auto encoded_data = vec::Vec<str::String>();
    for (size_t i = 0; i < data.len(); ++i) {
        auto encoded_s = caeser_cypher::encode(data.get(i), cypher_words, stats);
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

void RunCaesarCypher(args_parser::ParsedFilenames filenames, caeser_cypher::TotalCypherStats& stats) {
    auto cypher_file_data = fs::ReadAllVec(filenames.cypher_file, CYPHER_LEN);
    auto cyphere_file_as_str = str::Joined(cypher_file_data);
    auto cypher_file_words = str::Split(cyphere_file_as_str);

    auto cypher_words = caeser_cypher::NewCypherWords(cypher_file_words);

    auto input_file_data = fs::ReadAllVec(filenames.input_file, WORD_LEN);
    auto input_data_as_str = str::Joined(input_file_data);
    auto input_data = str::GroupedBy(input_data_as_str, WORD_LEN);

    stats.input_text_len = str::Len(input_data_as_str);
    stats.cypher_notebook_len = cypher_file_words.len();

    auto encoded_data = Encode(input_data, cypher_words, stats);
    fs::WriteAllVec(filenames.encoded_output_file, encoded_data);

    auto decoded_data = Decode(encoded_data, cypher_words);
    fs::WriteAllVec(filenames.decoded_output_file, decoded_data);
}

}  // namespace

namespace app {
void Run(args_parser::ParsedFilenames filenames) {
    if (!args_parser::IsFilledStruct(filenames)) {
        std::cerr << "Failed to parse args!" << std::endl;
        args_parser::PrintHelp();

        return;
    }

    caeser_cypher::TotalCypherStats statistics = {};

    RunCaesarCypher(filenames, statistics);
    PrintStatistics(statistics);
}
}  // namespace app
