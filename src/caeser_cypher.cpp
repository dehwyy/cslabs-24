#include "caeser_cypher.h"
#include <iostream>

namespace {
const int MOD = 128;
void NewSymbolOrIncrement(caeser_cypher::TotalCypherStats& stats, char ch, char encoded_ch) {
    size_t ch_idx = ch - 1;

    ++stats.symbols[ch_idx].total;
    if (!stats.symbols[ch_idx].s) {
        stats.symbols[ch_idx].s = ch;
        stats.symbols[ch_idx].different_encodes.push(encoded_ch);
    } else {
        if (!stats.symbols[ch_idx].different_encodes.contains(encoded_ch)) {
            stats.symbols[ch_idx].different_encodes.push(encoded_ch);
        }
    }
}
}  // namespace

namespace caeser_cypher {
CypherWords::CypherWords(const vec::Vec<str::String>& codewords) : cypher_codes(vec::Vec<char>()) {
    for (size_t i = 0; i < codewords.len(); i++) {
        int codeword_sum = 0;
        str::String codeword = codewords.get(i);

        for (size_t j = 0; j < codeword.len(); j++) {
            codeword_sum += codeword.get_char(j);
        }

        char ch = static_cast<char>(codeword_sum % MOD);

        this->cypher_codes.push(ch);
    }
}
char CypherWords::get_wrapped(size_t idx) {
    size_t len = this->cypher_codes.len();
    if (idx >= len && len != 0) {
        idx = idx % len;
    }

    return this->cypher_codes.get(idx);
}

str::String encode(str::String s, CypherWords& cypher_words, TotalCypherStats& stats) {
    auto buf = vec::Vec<char>();
    for (size_t i = 0; i < s.len(); i++) {
        char ch = s.get_char(i);

        int encoded_value = (ch + cypher_words.get_wrapped(i)) % MOD + 1;
        char encoded_ch = static_cast<char>(encoded_value);

        NewSymbolOrIncrement(stats, ch, encoded_ch);
        buf.push(encoded_ch);
    }

    auto encoded_s = str::String(buf);

    return encoded_s;
}

str::String decode(str::String s, CypherWords& cypher_words) {
    auto buf = vec::Vec<char>();
    for (size_t i = 0; i < s.len(); i++) {
        int decoded_value = (s.get_char(i) - 1 - cypher_words.get_wrapped(i)) % MOD;

        if (decoded_value < 0) {
            decoded_value += MOD;
        }

        char decoded_ch = static_cast<char>(decoded_value);
        buf.push(decoded_ch);
    }

    auto decoded_s = str::String(buf);

    return decoded_s;
}
}  // namespace caeser_cypher
