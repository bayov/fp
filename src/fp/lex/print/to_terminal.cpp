#include <fp/util/ansi/codes.h>

#include "to_terminal.h"

namespace fp::lex::print {

using namespace util::ansi;

void to_terminal(std::ostream& os, const token& t) {
    graphics_code color;
    switch (t) {
        case token::IDENTIFIER:
            color = magenta;
            break;
        case token::ERROR:
            color = red;
            break;
        default:
            color = cyan;
    }
    if (is_keyword(t)) { color = yellow; }
    os << color << token_name(t) << reset;
}

void to_terminal(std::ostream& os, const tokenized_token& t) {
    to_terminal(os, t.token);
    os << grey << " (" << t.source_location.chars << ')';
    if (t.dummy && t.token != token::ERROR) { os << red << " [dummy]"; }
    os << reset;
}

void to_terminal(std::ostream& os, const tokenized_list& tokens) {
    for (const auto& t : tokens) {
        to_terminal(os, t);
        os << '\n';
    }
}

} // namespace fp::lex::print
