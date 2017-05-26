#pragma once

#include <fp/util/named_tuple.h>
#include <fp/common/input.h>

namespace fp {

/// Information about the location of an element in the source code.
NAMED_TUPLE(
    source_location,
    (input_view, symbols)   ///< The symbols that make up the element.
    (symbol_iterator, line) ///< The beginning of the line of the element.
    (size_t, line_number)   ///< The element's line number.
    (input_view, input)     ///< The entire source code.
);

} // namespace fp
