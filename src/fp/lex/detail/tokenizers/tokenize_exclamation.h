#pragma once

#include <fp/lex/detail/tokenizer_state.h>

namespace fp::lex::detail {

/// Tokenize `!=` (token::NE).
inline void tokenize_exclamation(tokenizer_state& s) {
    ++s.it;
    if (*s.it == '=') {
        s.tokenize_as<token::NE>();
    } else {
        s.error("Invalid symbol. Did you mean `not` or `!=`?");
        s.push<token::ERROR_OP>();
    }
}

} // namespace fp::lex::detail
