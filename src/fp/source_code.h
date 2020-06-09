#pragma once

#include <string>
#include <string_view>

namespace fp {

/// A reference to a section of input source code.
using source_view = std::string_view;

/// A piece of source code that is given as an input to the compiler.
struct source_file {
    /// The name of the source code (usually the name of the source file).
    std::string name;
    /// The contents of the source code.
    source_view content;

    source_file(std::string name, std::string content);
    source_file(std::string name, std::string_view content);
    source_file(std::string name, const char* content);

    bool operator==(const source_file& other) const { return this == &other; }

private:
    /**
     * Used only when owning the data, in which case source_code::contents is
     * just a view to this string. Otherwise, this string is empty and
     * source_code::content points to a string that someone else owns.
     */
    std::string content_data;
};

/// Iterator pointing to a character in a source code.
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
struct source_location {
    /// The range of characters that make up the element.
    source_view chars;
    /// The relevant source code file.
    const source_file& file;
    /// Iterator to the beginning of the location's line.
    source_iterator line;
    /// The line number of the location relative to `file`.
    size_t line_number;

    //@{
    /**
     * Returns a slice of the source-location starting from iterator `first`,
     * and continuing up to character `last`. If `last` is not given, the slice
     * will continue until `chars.end()`.
     *
     * This function assumes that `first` and `last` are valid iterators to the
     * `chars` source-view.
     */
    source_location slice(source_iterator first) const;
    source_location slice(source_iterator first, source_iterator last) const;
    //@}

    /**
     * Returns a slice to one after the last character in the source-location.
     *
     * Equivalent to `location.slice(location.chars.end())`.
     */
     source_location slice_end() const;
};

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
