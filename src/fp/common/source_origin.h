#pragma once

#include <fp/util/named_tuple.h>

#include "symbol.h"

namespace fp {

/// Information about the original source of an element.
NAMED_TUPLE(
    source_origin,
    (input_view_t, symbols)(symbol_iterator, line)(size_t, line_number)
);

} // fp
