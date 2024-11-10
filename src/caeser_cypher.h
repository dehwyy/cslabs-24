#include "collections/str.h"
#include "collections/vec.h"

namespace caeser_cypher {
struct CypherWords {
    CypherWords(const vec::Vec<str::String>& codewords);
    char get_wrapped(size_t idx);

 private:
    vec::Vec<char> cypher_codes;
};

struct SymbolCypherStats {
    char s = 0;
    unsigned total = 0;
    vec::Vec<char> different_encodes = {};
};

struct TotalCypherStats {
    SymbolCypherStats symbols[128] = {};
    size_t cypher_notebook_len = 0;
    size_t input_text_len = 0;
};

str::String encode(str::String s, CypherWords& cypher_words, TotalCypherStats& stats);
str::String decode(str::String s, CypherWords& cypher_words);
}  // namespace caeser_cypher
