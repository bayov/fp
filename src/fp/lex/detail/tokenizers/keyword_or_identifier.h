#pragma once

#include <fp/lex/token.h>
#include <fp/lex/detail/characters_range.h>
#include <fp/lex/detail/tokenization_state.h>

namespace fp::lex::detail {

/// Tokenizes either a language keyword or an identifier.
inline void tokenize_keyword_or_identifier(tokenization_state& s) {
    // consume all keyword/identifier characters
    do {
        ++s.next;
    } while(s.next != s.end && identifier_characters::contain(*s.next));

    auto it = keywords_map.find(s.current_token_characters());
    if (it != keywords_map.end()) {
        s.push(it->second);
    } else {
        s.push<token::IDENTIFIER>(s.current_token_characters());
    }
}

} // namespace fp::lex::detail
