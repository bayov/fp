#pragma once

#include <fp/lex/detail/tokenization_state.h>

namespace fp::lex::detail {

/// Tokenizes either `:` (token::ANNOTATION) or `::` (token::SCOPE).
inline void tokenize_colon(tokenization_state& s) {
    ++s.next;
    if (s.next_is(':')) {
        s.consume_and_push(token::SCOPE);
    } else {
        s.push(token::ANNOTATION);
    }
}

} // namespace fp::lex::detail
