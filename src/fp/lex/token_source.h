#pragma once

#include <fp/util/named_tuple.h>

#include "symbol.h"

namespace fp::lex {

/// Information about the original symbols that a token was created from.
NAMED_TUPLE(
    token_source,
    (input_view_t, symbols)(symbol_iterator, line)(size_t, line_number)
);

} // fp::lex
