#pragma once

#include <fp/util/with.h>
#include <fp/syntax/detail/parsing_state.h>
#include <fp/syntax/detail/token_table_t.h>
#include <fp/syntax/detail/parse_prefix.h>

namespace fp::syntax::detail {

using infix_parser_t = ast::node (*)(parsing_state&, ast::node lhs);

inline ast::node parse_infix_error(parsing_state& s, ast::node lhs) {
    s.report_error("unexpected token")
        .add_primary(s.next->source_location)
        .add_contextual(lhs.source_location());
    ++s.next;
    return ast::infix_error(std::move(lhs), s.next - 1);
}

constexpr auto infix_parser_table = token_table_t<infix_parser_t>([](auto& t) {
     t.set_default(parse_infix_error);

//    // binary-operators
//    t[lex::token::COMMA] = parsers::binary_op;
//    t[lex::token::ANNOTATION] = parsers::binary_op;
//    t[lex::token::SCOPE] = parsers::binary_op;
//    t[lex::token::SEMICOLON] = parsers::binary_op;
//    t[lex::token::MEMBER_ACCESS] = parsers::binary_op;
//    t[lex::token::RANGE] = parsers::binary_op;
//    t[lex::token::CLOSED_RANGE] = parsers::binary_op;
//    t[lex::token::TYPE_ARROW] = parsers::binary_op;
//    t[lex::token::LAMBDA_ARROW] = parsers::binary_op;
//    t[lex::token::PLUS] = parsers::binary_op;
//    t[lex::token::MINUS] = parsers::binary_op;
//    t[lex::token::MUL] = parsers::binary_op;
//    t[lex::token::DIV] = parsers::binary_op;
//    t[lex::token::MOD] = parsers::binary_op;
//    t[lex::token::POW] = parsers::binary_op;
//    t[lex::token::BIT_AND] = parsers::binary_op;
//    t[lex::token::BIT_OR] = parsers::binary_op;
//    t[lex::token::XOR] = parsers::binary_op;
//    t[lex::token::LSHIFT] = parsers::binary_op;
//    t[lex::token::RSHIFT] = parsers::binary_op;
//    t[lex::token::ASSIGN] = parsers::binary_op;
//    t[lex::token::PLUS_ASSIGN] = parsers::binary_op;
//    t[lex::token::MINUS_ASSIGN] = parsers::binary_op;
//    t[lex::token::MUL_ASSIGN] = parsers::binary_op;
//    t[lex::token::DIV_ASSIGN] = parsers::binary_op;
//    t[lex::token::MOD_ASSIGN] = parsers::binary_op;
//    t[lex::token::POW_ASSIGN] = parsers::binary_op;
//    t[lex::token::BIT_AND_ASSIGN] = parsers::binary_op;
//    t[lex::token::BIT_OR_ASSIGN] = parsers::binary_op;
//    t[lex::token::XOR_ASSIGN] = parsers::binary_op;
//    t[lex::token::LSHIFT_ASSIGN] = parsers::binary_op;
//    t[lex::token::RSHIFT_ASSIGN] = parsers::binary_op;
//    t[lex::token::EQ] = parsers::binary_op;
//    t[lex::token::NE] = parsers::binary_op;
//    t[lex::token::LT] = parsers::binary_op;
//    t[lex::token::GT] = parsers::binary_op;
//    t[lex::token::LTE] = parsers::binary_op;
//    t[lex::token::GTE] = parsers::binary_op;
//
//    // postfix-operators
//    t[lex::token::OPTIONAL] = parsers::postfix_op;
//    t[lex::token::INC] = parsers::postfix_op;
//    t[lex::token::DEC] = parsers::postfix_op;
//
//    // error
//    t[lex::token::ERROR] = infix_parser_skip_error;
});

inline ast::node parse_infix(parsing_state& s, ast::node lhs) {
    return infix_parser_table[s.next->token](s, std::move(lhs));
}

} // namespace fp::syntax::detail
