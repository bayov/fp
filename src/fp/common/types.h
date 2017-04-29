#pragma once

#include <cstdint>
#include <string>
#include <string_view>

#include <boost/range/iterator_range.hpp>

namespace fp {

/// The type representing integers in the compiler.
using integer_type = uint64_t;

/// The type representing floating-points in the compiler.
using float_type = double;

/// The type representing character in the compiler.
using char_type = char32_t;

/// Represents a symbol in a source file.
using symbol_t = char;

/// Represents a source file (as a string of @ref symbol_t).
using input = std::basic_string<symbol_t>;

/// An iterator to a @ref symbol_t in an @ref input_t.
using symbol_iterator = input::const_iterator;

/// A view to a range inside of an @ref input_t.
struct input_view : boost::iterator_range<symbol_iterator> {
    using boost::iterator_range<symbol_iterator>::iterator_range;
    explicit operator input() const { return { begin(), end() }; };
    explicit operator std::string_view() const { return { &front(), size() }; }
};

} // namespace fp
