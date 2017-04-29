#pragma once

#include <boost/range/iterator_range.hpp>

#include "token_list.h"

namespace fp::lex {

/// An iterator to a @ref token_value in a @ref token_list.
using token_iterator = token_list::const_iterator;

/// A view to a range inside of a @ref token_list.
struct token_view : boost::iterator_range<token_iterator> {

    using boost::iterator_range<token_iterator>::iterator_range;

    operator source_origin() const {
        return {
            { front().origin.symbols.begin(), back().origin.symbols.end() },
            front().origin.line,
            front().origin.line_number
        };
    }

};

} // namespace fp::lex
