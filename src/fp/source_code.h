#pragma once

#include <string>
#include <string_view>

#include <fp/util/record.h>

namespace fp {

/// Represents a single character in an input source file.
using source_char = char;

/// A piece of source code that is given as an input to the compiler.
using source_code = std::basic_string<source_char>;

/// A reference to a section of input source code.
using source_view = std::basic_string_view<source_char>;

/// Iterator pointing to a character in the source code.
using source_iterator = source_view::iterator;

/**
 * Information about a location in a piece of source code. Each compiler element
 * will hold an instance of this to keep track of its origin in the source code.
 */
FP_RECORD(source_location,
     /// The range of characters that make up the element.
    (source_view, chars)
    /// The entire source code being compiled in this context.
    (source_view, source_code)
    /// Iterator to the beginning of the location's line.
    (source_iterator, line)
    /// The line number of the location relative to `source_code`.
    (size_t, line_number)
);

/**
 * Returns a merged source location from the two given locations `first` and
 * `second`. The result is all characters between the first character in `first`
 * to the last character in `second`.
 *
 * Assumes that both locations originated from the same source_code, so
 * `first.source_code` is used.
 */
source_location merge(
    const source_location& first,
    const source_location& second
);

} // namespace fp
