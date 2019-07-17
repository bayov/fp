#pragma once

#include <fp/lex/detail/tokenization_state.h>

namespace fp::lex::detail {

/// Push a token::ERROR and report a diagnostic::error.
inline void stray_character(tokenization_state& s) {
    s.consume_and_push<token::ERROR>();
    s.report_error("stray character in source code");
}

} // namespace fp::lex::detail
