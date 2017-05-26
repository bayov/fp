#include <fp/parse/detail/parser_state.h>
#include <fp/parse/detail/precedence.h>
#include <fp/parse/detail/prefix_parser.h>
#include <fp/parse/detail/infix_parser.h>

#include "parse.h"

namespace fp::parse {

namespace detail {

/**
 * Parse the next set of tokens of the given parser state.
 *
 * Implemented using the Pratt Parser (TDOP) algorithm.
 */
ast::node parse(parser_state& s, precedence_t p) {
    if (s.it == s.end) { return ast::make<ast::empty>(s.end, s.end); }
    ast::node lhs = parse_prefix(s);
    while (p < precedence_table[s.it->value]) {
        lhs = parse_infix(s, std::move(lhs));
    }
    return lhs;
}

} // namespace detail

ast::node parse(const lex::token_view& tokens, diagnostic_report& diagnostics) {
    detail::parser_state s(tokens, detail::parse, diagnostics);
    ast::node lhs = parse(s, 0);
    while (s.it != s.end) { lhs = parse_infix(s, std::move(lhs)); }
    return lhs;
}

} // namespace fp::parse
