#include <iomanip>

#include <fp/util/match.h>

#include "tokenized_list.h"

namespace fp::lex {

namespace detail {

void print_token_attribute(std::ostream& os, token, char_t c) {
    if (c == token_dummy_value<token::CHAR>) {
        os << "<dummy>";
    } else {
        os << "0x" << std::setfill('0') << std::setw(2) << std::hex << c;
    }
}

template <class T>
void print_token_attribute(std::ostream& os, token, const T&) {
    os << "xxx";
}

} // namespace detail

std::ostream& operator<<(std::ostream& os, const tokenized_token& t) {
    util::match(t.attribute)(
        [&](std::monostate) { os << t.token; },
        [&](const auto& value) {
            os << t.token << '[';
            detail::print_token_attribute(os, t.token, value);
            os << ']';
        }
    );
    return os << " (line " << t.source_location.line_number << ')';
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
