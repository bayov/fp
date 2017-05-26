#pragma once

#include <boost/range/iterator_range.hpp>

#include <fp/lex/token_list.h>

namespace fp::lex {

/// An iterator to a @ref token_value in a @ref token_list.
using token_iterator = token_list::iterator;

/// A view to a range inside of a @ref token_list.
struct token_view : boost::iterator_range<token_iterator> {

    using boost::iterator_range<token_iterator>::iterator_range;

    operator source_location() const {
        const source_location* source;
        input_view symbols;
        if (empty()) {
            // `begin() - ` is guaranteed to exist, because token_list always
            // contains a dummy HEAD token
            source = &(begin() - 1)->source;
            symbols = { source->symbols.end(), source->symbols.end() };
        } else {
            source = &front().source;
            symbols = { source->symbols.begin(), back().source.symbols.end() };
        }
        return {
            std::move(symbols),
            source->line,
            source->line_number,
            source->input
        };
    }

};

} // namespace namespace fp::lex
