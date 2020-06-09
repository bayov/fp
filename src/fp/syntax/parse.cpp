#include <fp/syntax/detail/precedence.h>
#include <fp/syntax/detail/parsing_state.h>
#include <fp/syntax/detail/parse_prefix.h>
#include <fp/syntax/detail/parse_infix.h>

#include "parse.h"

namespace fp::syntax {

namespace detail {

static ast::node parse(parsing_state& s, precedence_t p) {
    if (s.next == s.end) { return ast::empty(s.end, s.end); }
    ast::node lhs = parse_prefix(s);
    while (s.next != s.end && p < precedence_table[s.next->token]) {
        lhs = parse_infix(s, std::move(lhs));
    }
    return lhs;
}

} // namespace detail

ast::node parse(lex::tokenized_view tokens, diagnostic::report& report) {
    // Parsing is implemented using a simple Pratt Parser (TDOP) algorithm
    detail::parsing_state s(tokens, detail::parse, report);
    ast::node lhs = s.parse(0);
    while (s.next != s.end) { lhs = detail::parse_infix(s, std::move(lhs)); }
    return lhs;
}

} // namespace fp::syntax
