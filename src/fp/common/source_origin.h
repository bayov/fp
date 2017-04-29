#pragma once

#include <fp/util/named_tuple.h>

#include "types.h"

namespace fp {

/// Information about the original source of an element.
NAMED_TUPLE(
    source_origin,
    (input_view, symbols)(symbol_iterator, line)(size_t, line_number)
);

} // fp
