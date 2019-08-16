#pragma once

#include <fp/syntax/detail/parsing_state.h>
#include <fp/syntax/detail/token_table_t.h>
#include <fp/syntax/detail/parsers/single_token.h>

namespace fp::syntax::detail {

using prefix_parser_t = ast::node (*)(parsing_state&);

inline ast::node parse_prefix_error(parsing_state& s) {
    s.report_error("Invalid token");
    ++s.next;
    return ast::error(s.next - 1, s.next);
}

//inline ast::node prefix_parser_skip_error(parser_state& s) {
//    ++s.it;
//    return ast::make<ast::error>(s.it - 1, s.it);
//}

constexpr auto prefix_parser_table = token_table_t<prefix_parser_t>([](auto& t) {
    t.set_default(parse_prefix_error);

    // identifiers and literals
    t[lex::token::IDENTIFIER] = parse_single_token<ast::identifier>;
    t[lex::token::NUMBER] = parse_single_token<ast::number>;

    // language constructs
//    t[lex::token::IMPORT] = parsers::import;
//
//    // prefix-operators
//    t[lex::token::DECORATOR] = parsers::prefix_op;
//    t[lex::token::BIT_NOT] = parsers::prefix_op;
//    t[lex::token::PLUS] = parsers::prefix_op;
//    t[lex::token::MINUS] = parsers::prefix_op;
//    t[lex::token::BIT_AND] = parsers::prefix_op;
//    t[lex::token::INC] = parsers::prefix_op;
//    t[lex::token::DEC] = parsers::prefix_op;
//
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
