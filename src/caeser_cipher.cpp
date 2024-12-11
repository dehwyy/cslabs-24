#include "caeser_cipher.h"
#include <iostream>

namespace {
const int MOD = 128;
void NewSymbolOrIncrement(caeser_cipher::TotalCipherStats& stats, char ch, char encoded_ch) {
    int ch_idx = ch;
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

namespace caeser_cipher {

CipherWords NewCipherWords(const vec::Vec<str::String>& codewords) {
    auto cipher_codes = vec::Vec<char>();
    for (size_t i = 0; i < codewords.len(); i++) {
        int codeword_sum = 0;
        str::String codeword = codewords.get(i);

        for (size_t j = 0; j < str::Len(codeword); j++) {
            codeword_sum += str::GetChar(codeword, j);
        }

        char ch = static_cast<char>(codeword_sum % MOD);

        cipher_codes.push(ch);
    }

    auto v = CipherWords{.cipher_codes = cipher_codes};

    return v;
}

char GetWrappedCipherWordCode(const CipherWords& cipher_words, size_t idx) {
    size_t len = cipher_words.cipher_codes.len();
    if (idx >= len && len != 0) {
        idx = idx % len;
    }

    return cipher_words.cipher_codes.get(idx);
}

str::String encode(str::String s, CipherWords& cipher_words, TotalCipherStats& stats) {
    std::cout << std::endl;
    auto buf = vec::Vec<char>();
    for (size_t i = 0; i < str::Len(s); i++) {
        char ch = str::GetChar(s, i);
        int encoded_value = (ch + GetWrappedCipherWordCode(cipher_words, i)) % MOD + 1;
        char encoded_ch = static_cast<char>(encoded_value);

        NewSymbolOrIncrement(stats, ch, encoded_ch);
        buf.push(encoded_ch);
    }

    auto encoded_s = str::FromVec(buf);

    return encoded_s;
}

str::String decode(str::String s, CipherWords& cipher_words) {
    auto buf = vec::Vec<char>();
    for (size_t i = 0; i < str::Len(s); i++) {
        int decoded_value = (str::GetChar(s, i) - 1 - GetWrappedCipherWordCode(cipher_words, i)) % MOD;

        if (decoded_value < 0) {
            decoded_value += MOD;
        }

        char decoded_ch = static_cast<char>(decoded_value);
        buf.push(decoded_ch);
    }

    auto decoded_s = str::FromVec(buf);

    return decoded_s;
}
}  // namespace caeser_cipher
