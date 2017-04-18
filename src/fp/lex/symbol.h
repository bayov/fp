#pragma once

#include <string>
#include <string_view>

#include <boost/range/iterator_range.hpp>

namespace fp::lex {

/// Represents a symbol in a source file (as input to the lexer).
using symbol_t = char;

/// The type of the input to the lexer (as a range of @ref symbol_t).
using input_t = std::basic_string<symbol_t>;

/// An iterator to a @ref symbol_t in an @ref input_t.
using symbol_iterator = input_t::const_iterator;

/// A view to a slice of @ref input_t.
struct input_view_t : boost::iterator_range<symbol_iterator> {
    using boost::iterator_range<symbol_iterator>::iterator_range;
    operator input_t() const { return { begin(), end() }; };
    std::string_view view() const { return { &*begin(), size() }; }
};

inline input_view_t make_input_view(const input_t& input) {
    return { input.begin(), input.end() };
}

} // namespace fp::lex
