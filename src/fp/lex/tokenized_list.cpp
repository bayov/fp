#include <fp/lex/print/to_terminal.h>

#include "tokenized_list.h"

namespace fp::lex {

std::ostream& operator<<(std::ostream& os, tokenized_view tokens) {
    fp::lex::print::to_terminal(os, tokens);
    return os;
}

source_location get_source_location(tokenized_view tokens) {
    if (tokens.empty()) {
        throw std::invalid_argument(
            "get_source_location called on an empty tokenized_view"
        );
    }
    return merge(tokens.front().source_location, tokens.back().source_location);
}

} // namespace namespace fp::lex
