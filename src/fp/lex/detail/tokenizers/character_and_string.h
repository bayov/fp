#pragma once

#include <fp/lex/detail/tokenization_state.h>

namespace fp::lex::detail {

/// Tokenizes a single character (token::CHAR).
void tokenize_character(tokenization_state&);

/**
 * Tokenizes a double-quote (token::QUOTE), a string section (token::STRING) if
 * it's not empty, and a terminator (either token::QUOTE or token::L_BRACE).
 */
void tokenize_double_quote(tokenization_state&);

/**
 * Tokenizes a left-brace (token::L_BRACE). If we're currently in a string
 * context, this starts a string interpolation.
 */
void tokenize_left_brace(tokenization_state&);

/**
 * Tokenizes a right-brace (token::R_BRACE). Also updates the open left-braces
 * count when inside a string interpolation.
 */
void tokenize_right_brace(tokenization_state&);

} // namespace fp::lex::detail
