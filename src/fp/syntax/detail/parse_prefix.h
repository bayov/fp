#pragma once

#include <fp/syntax/detail/parsing_state.h>
#include <fp/syntax/detail/token_table_t.h>
#include <fp/syntax/detail/parsers/prefix_op.h>
#include <fp/syntax/detail/parsers/single_token.h>

namespace fp::syntax::detail {

using prefix_parser_t = ast::node (*)(parsing_state&);

inline ast::node parse_prefix_error(parsing_state& s) {
    s.report_error("Invalid token");
    ++s.next;
    return ast::error(s.next - 1, s.next);
}

constexpr auto prefix_parser_table = token_table_t<prefix_parser_t>([](auto& t) {
    t.set_default(parse_prefix_error);

    // identifiers and literals
    t[lex::token::IDENTIFIER] = parse_single_token<ast::identifier>;
    t[lex::token::NUMBER] = parse_single_token<ast::number>;

    // language constructs
//    t[lex::token::IMPORT] = parsers::import;

    // prefix-operators
    t[lex::token::DECORATOR] = parse_prefix_op;
    t[lex::token::BIT_NOT]   = parse_prefix_op;
    t[lex::token::ADD]       = parse_prefix_op;
    t[lex::token::SUB]       = parse_prefix_op;
    t[lex::token::BIT_AND]   = parse_prefix_op;
    t[lex::token::INC]       = parse_prefix_op;
    t[lex::token::DEC]       = parse_prefix_op;

//    // error
//    t[lex::token::ERROR] = prefix_parser_skip_error;
//
//    return t;
});

inline ast::node parse_prefix(parsing_state& s) {
    ast::node node = prefix_parser_table[s.next->token](s);
//    if (node.is<ast::error>()) {
//        // try to recover from the error by parsing until succeeding, while
//        // ignoring all errors along the way to avoid diagnostics clutter
//        WITH(s.ignore_diagnostics_in_scope()) {
//            while (
//                s.it != s.end &&
//                prefix_parser_table[s.it->value](s).is<ast::error>()
//            ) {}
//        }
//    }
    return node;
}

} // namespace fp::syntax::detail
