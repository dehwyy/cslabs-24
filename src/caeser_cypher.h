#include "internal/str.h"
#include "internal/vec.h"

namespace caeser_cypher {
struct CypherWords {
    CypherWords(vec::Vec<str::String>& codewords);
    char get_wrapped(size_t idx);

 private:
    vec::Vec<char> cypher_codes;
};

void encode(str::String s, vec::Vec<char>& buf, CypherWords& cypher_words);
void decode(str::String s, vec::Vec<char>& buf, CypherWords& cypher_words);
}  // namespace caeser_cypher
