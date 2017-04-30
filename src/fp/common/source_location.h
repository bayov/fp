#pragma once

#include <fp/util/named_tuple.h>
#include <fp/common/input.h>

namespace fp {

/// Information about the location of an element in the source code.
NAMED_TUPLE(
    source_location,
    (input_view, symbols)(symbol_iterator, line)(size_t, line_number)
);

} // fp
