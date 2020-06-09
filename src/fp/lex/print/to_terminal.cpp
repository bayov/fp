#include <fp/util/ansi/codes.h>

#include "to_terminal.h"

namespace fp::lex::print {

using namespace util::ansi;

void to_terminal(std::ostream& os, const tokenized_token& t) {
    graphics_code color;
    switch (t.token) {
        case token::IDENTIFIER:
            color = magenta;
            break;
        case token::NUMBER:
            color = blue;
            break;
        case token::ERROR:
            color = red;
            break;
        default:
            color = default_color;
    }
    if (is_keyword(t.token)) { color = yellow; }
    os << color << t.source_location.chars << reset;
    os << grey << " (token::" << token_name(t.token) << ')';
    if (t.dummy && t.token != token::ERROR) { os << red << " [dummy]"; }
    os << reset;
}

void to_terminal(std::ostream& os, tokenized_view tokens) {
    for (const auto& t : tokens) {
        to_terminal(os, t);
        os << '\n';
    }
}

} // namespace fp::lex::print
