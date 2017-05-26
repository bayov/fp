#pragma once

#include <fp/lex/detail/tokenizer_state.h>

namespace fp::lex::detail {

/**
 * Tokenize one of:
 *
 *      - `:`   (token::ANNOTATION)
 *      - `::`  (token::SCOPE)
 *
 */
inline void tokenize_colon(tokenizer_state& s) {
    if (s.next_is<':'>()) {
        ++s.it;
        s.tokenize_as<token::SCOPE>();
    } else {
        s.tokenize_as<token::ANNOTATION>();
    }
}

} // namespace fp::lex::detail
