#include "collections/str.h"
#include "collections/vec.h"

namespace caeser_cipher {
struct CipherWords {
    vec::Vec<char> cipher_codes;
};

struct SymbolCipherStats {
    char s = 0;
    unsigned total = 0;
    vec::Vec<char> different_encodes = {};
};

struct TotalCipherStats {
    SymbolCipherStats symbols[128] = {};
    size_t cipher_notebook_len = 0;
    size_t input_text_len = 0;
};

CipherWords NewCipherWords(const vec::Vec<str::String>& codewords);
char GetWrappedCipherWordCode(const CipherWords& cipher_words, size_t idx);

str::String encode(str::String s, CipherWords& cipher_words, TotalCipherStats& stats);
str::String decode(str::String s, CipherWords& cipher_words);
}  // namespace caeser_cipher
