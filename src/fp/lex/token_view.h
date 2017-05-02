#pragma once

#include <boost/range/iterator_range.hpp>

#include <fp/lex/token_list.h>

namespace fp::lex {

/// An iterator to a @ref token_value in a @ref token_list.
using token_iterator = token_list::const_iterator;

/// A view to a range inside of a @ref token_list.
struct token_view : boost::iterator_range<token_iterator> {

    using boost::iterator_range<token_iterator>::iterator_range;

    operator source_location() const {
        return {
            { front().source.symbols.begin(), back().source.symbols.end() },
            front().source.line,
            front().source.line_number
        };
    }

};

} // namespace namespace fp::lex
