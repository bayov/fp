#pragma once

#include <fp/lex/detail/tokenizer_state.h>

namespace fp::lex::detail {

inline void tokenize_exclamation(tokenizer_state& s) {
    if (!s.next_is<'='>()) {
        s.error("Invalid symbol. Did you mean `not` or `!=`?");
    }
    s.it += 2;
    s.push<token::NE>();
}

} // fp::lex::detail
