#pragma once

#include <fp/lex/detail/tokenization_state.h>

namespace fp::lex::detail {

/// Skips the next character without doing anything.
inline void ignore(tokenization_state& s) { ++s.next; }

/// Skips over the next character and begin a new line.
inline void line_feed(tokenization_state& s) {
    ++s.next;
    s.begin_new_line();
}

/// Just like tokenizer::line_feed, but also skips a CRLF combination ("\r\n").
inline void carriage_return(tokenization_state& s) {
    ++s.next; // skip '\r'
    if (s.next_is<'\n'>()) { ++s.next; }
    s.begin_new_line();
}

} // namespace fp::lex::detail
