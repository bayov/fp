#pragma once

#include <string>
#include <string_view>

#include <boost/range/iterator_range.hpp>

namespace fp {

/// Represents a symbol in a source file.
using symbol_t = char;

/// Represents a source file (as a string of @ref symbol_t).
using input_t = std::basic_string<symbol_t>;

/// An iterator to a @ref symbol_t in an @ref input_t.
using symbol_iterator = input_t::const_iterator;

/// A view to a range inside of an @ref input_t.
struct input_view_t : boost::iterator_range<symbol_iterator> {
    using boost::iterator_range<symbol_iterator>::iterator_range;
    explicit operator input_t() const { return { begin(), end() }; };
    std::string_view view() const { return { &*begin(), size() }; }
};

} // namespace fp
