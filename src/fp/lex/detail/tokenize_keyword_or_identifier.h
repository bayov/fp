#pragma once

#include <unordered_map>
#include <string_view>

#include <fp/lex/keywords.h>

#include "tokenizer_state.h"
#include "identifier_symbols.h"

namespace fp::lex::detail {

#define FP_KEYWORD_MAP_ITEM(enumerator, name) { name, token::enumerator },

/// A mapping from keyword strings to their matching tokens.
inline std::unordered_map<std::string_view, token> create_keywords_map() {
    return { FP_KEYWORDS_FOR_EACH(FP_KEYWORD_MAP_ITEM) };
}

/// Skip symbols until reaching a non-identifier symbol.
inline void skip_to_end_of_identifier(tokenizer_state& s) {
    while (s.it != s.end && identifier_symbols::contain(*s.it)) { ++s.it; }
}

/// Tokenize an identifier.
inline void tokenize_identifier(tokenizer_state& s) {
    skip_to_end_of_identifier(s);
    s.push<token::IDENTIFIER>(s.token_symbols());
}

/// Tokenize either a language keyword (FP_KEYWORDS) or an identifier.
inline void tokenize_keyword_or_identifier(tokenizer_state& s) {
    static const auto keywords_map = create_keywords_map();
    skip_to_end_of_identifier(s);
    auto it = keywords_map.find(std::string_view(s.token_symbols()));
    if (it != keywords_map.end()) {
        s.push(it->second);
    } else {
        s.push<token::IDENTIFIER>(s.token_symbols());
    }
}

} // fp::lex::detail
