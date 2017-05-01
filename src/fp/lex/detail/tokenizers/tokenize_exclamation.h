#pragma once

#include <fp/lex/detail/tokenizer_state.h>

namespace fp::lex::detail {

/// Tokenize `!=` (token::NE).
inline void tokenize_exclamation(tokenizer_state& s) {
    if (s.next_is<'='>()) {
        ++s.it;
        s.tokenize_as<token::NE>();
    } else {
        s.error("Invalid symbol. Did you mean `not` or `!=`?");
        s.tokenize_as<token::ERROR_OP>();
    }
}

} // fp::lex::detail
