#pragma once

#include <fp/lex/detail/symbol_range.h>

namespace fp::lex::detail {

/// Contains all valid symbols of identifiers in the language.
using identifier_symbols = composite_symbol_range<
    symbol_range<'_', '_'>,
    symbol_range<'a', 'z'>,
    symbol_range<'A', 'Z'>,
    symbol_range<'0', '9'>
>;

} // namespace fp::lex::detail
