#pragma once

#include <fp/lex/detail/tokenizer_state.h>

namespace fp::lex::detail {

inline void tokenize_comment(tokenizer_state& s) {
    s.skip_to_end_of_line();
    s.push<token::COMMENT>(s.token_symbols());
}

} // fp::lex::detail
