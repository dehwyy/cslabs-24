#include "collections/str.h"
#include "collections/vec.h"

namespace caeser_cypher {
struct CypherWords {
    CypherWords(const vec::Vec<str::String>& codewords);
    char get_wrapped(size_t idx);

 private:
    vec::Vec<char> cypher_codes;
};

str::String encode(str::String s, CypherWords& cypher_words);
str::String decode(str::String s, CypherWords& cypher_words);
}  // namespace caeser_cypher
