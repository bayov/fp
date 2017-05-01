#pragma once

#include <fp/lex/detail/tokenizer_state.h>

namespace fp::lex::detail {

/**
 * Tokenize one of:
 *
 *      - `.`   (token::MEMBER_ACCESS)
 *      - `..`  (token::RANGE)
 *      - `...` (token::CLOSED_RANGE)
 *
 */
inline void tokenize_period(tokenizer_state& s) {
    if (s.next_is<'.'>()) {
        ++s.it;
        if (s.next_is<'.'>()) {
            ++s.it;
            s.tokenize_as<token::CLOSED_RANGE>();
        } else {
            s.tokenize_as<token::RANGE>();
        }
    } else {
        s.tokenize_as<token::MEMBER_ACCESS>();
    }
}

} // fp::lex::detail
