#pragma once

#include <fp/lex/detail/tokenization_state.h>

namespace fp::lex::detail {

/// Tokenizes TBD...
inline void tokenize_period(tokenization_state& s) {
    s.consume_and_push(token::MEMBER_ACCESS);
}

} // namespace fp::lex::detail