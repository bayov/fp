#pragma once

#include <fp/lex/detail/tokenization_state.h>

namespace fp::lex::detail {

/// Tokenizes a token::COMMENT.
inline void tokenize_comment(tokenization_state& s) {
    while (s.next != s.end && *s.next != '\n' && *s.next != '\r') { ++s.next; }
    s.push<token::COMMENT>(s.current_token_characters());
}

} // namespace fp::lex::detail