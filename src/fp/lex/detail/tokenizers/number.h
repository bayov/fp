#pragma once

#include <fp/lex/detail/tokenization_state.h>

namespace fp::lex::detail {

/**
 * Tokenizes a number that begins with a `0`, which could potentially be a base
 * specifier (0x / 0b / 0o).
 */
void tokenize_number_with_zero_prefix(tokenization_state&);

/// Tokenizes a number that does not begin with `0`.
void tokenize_number_with_no_zero_prefix(tokenization_state&);

} // namespace fp::lex::detail
