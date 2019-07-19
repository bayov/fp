#include <iomanip>

#include <fp/util/match.h>

#include "tokenized_list.h"

namespace fp::lex {

std::ostream& operator<<(std::ostream& os, const tokenized_token& t) {
    os << std::setw(14) << std::left << t.token << " : ";
    os << t.source_location.chars;
    if (t.dummy) { os << " (dummy)"; }
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
