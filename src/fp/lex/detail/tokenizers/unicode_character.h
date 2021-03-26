#pragma once

#include <fp/lex/detail/tokenization_state.h>

namespace fp::lex::detail {

/// Push a token::ERROR and report a diagnostic::error.
inline void unicode_character(tokenization_state& s) {
    s.consume_and_push(token::ERROR);
    s.report_error("unicode character not supported")
        .add_primary(
            s.current_token_location(),
            "unicode character (not supported)"
        );
}

} // namespace fp::lex::detail
