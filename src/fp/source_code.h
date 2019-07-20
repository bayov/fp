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

/// Construct a fp::source_view from the characters in range `[from, to)`.
constexpr source_view make_source_view(
    source_iterator from,
    source_iterator to
) {
    return source_view(from, to - from);
}

/// Returns a merged source code section. `first` must appear before `second`.
constexpr source_view merge(source_view first, source_view second) {
    return make_source_view(first.begin(), second.end());
}

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
 * Like fp::merge(source_view, source_view), but combines fp::source_location
 * instances.
 *
 * All other fields are taken from the `first` source location.
 */
constexpr source_location merge(
    const source_location& first,
    const source_location& second
) {
    source_location merged = first;
    merged.chars = merge(first.chars, second.chars);
    return merged;
}

} // namespace fp
