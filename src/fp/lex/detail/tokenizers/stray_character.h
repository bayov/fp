#pragma once

#include <fp/util/to_string.h>
#include <fp/error_codes.h>
#include <fp/lex/detail/tokenization_state.h>

namespace fp::lex::detail {

/// Push a token::ERROR and report a diagnostic::error.
inline void stray_character(tokenization_state& s) {
    char c = *s.next;
    s.consume_and_push(token::ERROR);

    std::ostringstream error_text;
    error_text << "stray character";
    if (c < ' ' || c == 127) { // unprintable
        error_text << ": \\" << std::oct << int16_t(c);
    }

    s.report_error(&error::E0001_stray_character)
        .add_primary(s.current_token_location(), error_text.str());
}

} // namespace fp::lex::detail
