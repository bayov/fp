#pragma once

#include <fp/lex/detail/tokenizer_state.h>

namespace fp::lex::detail {

/// Tokenize a comment, its content being all symbols to the end of the line.
inline void tokenize_comment(tokenizer_state& s) {
    while (s.it != s.end && *s.it != '\n' && *s.it != '\r') { ++s.it; }
    s.push<token::COMMENT>(s.token_symbols());
}

} // fp::lex::detail
