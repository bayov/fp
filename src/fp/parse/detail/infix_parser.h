#pragma once

#include <fp/ast/node.h>
#include <fp/parse/detail/parser_state.h>
#include <fp/parse/detail/parsers/binary_op.h>
#include <fp/parse/detail/parsers/postfix_op.h>
#include <fp/parse/detail/token_table_t.h>

namespace fp::parse::detail {

using infix_parser_t = ast::node (*)(parser_state&, ast::node);

inline ast::node infix_parser_non_infix(parser_state& s, ast::node lhs) {
    return lhs;
}

constexpr auto infix_parser_table = ([]() {
    auto t = token_table_t<infix_parser_t>::with_default(
        infix_parser_non_infix
    );

    // binary-operators
    t[lex::token::COMMA] = parsers::binary_op;
    t[lex::token::ANNOTATION] = parsers::binary_op;
    t[lex::token::MEMBER_ACCESS] = parsers::binary_op;
    t[lex::token::RANGE] = parsers::binary_op;
    t[lex::token::CLOSED_RANGE] = parsers::binary_op;
    t[lex::token::TYPE_ARROW] = parsers::binary_op;
    t[lex::token::LAMBDA_ARROW] = parsers::binary_op;
    t[lex::token::PLUS] = parsers::binary_op;
    t[lex::token::MINUS] = parsers::binary_op;
    t[lex::token::MUL] = parsers::binary_op;
    t[lex::token::DIV] = parsers::binary_op;
    t[lex::token::MOD] = parsers::binary_op;
    t[lex::token::POW] = parsers::binary_op;
    t[lex::token::BIT_AND] = parsers::binary_op;
    t[lex::token::BIT_OR] = parsers::binary_op;
    t[lex::token::XOR] = parsers::binary_op;
    t[lex::token::LSHIFT] = parsers::binary_op;
    t[lex::token::RSHIFT] = parsers::binary_op;
    t[lex::token::ASSIGN] = parsers::binary_op;
    t[lex::token::PLUS_ASSIGN] = parsers::binary_op;
    t[lex::token::MINUS_ASSIGN] = parsers::binary_op;
    t[lex::token::MUL_ASSIGN] = parsers::binary_op;
    t[lex::token::DIV_ASSIGN] = parsers::binary_op;
    t[lex::token::MOD_ASSIGN] = parsers::binary_op;
    t[lex::token::POW_ASSIGN] = parsers::binary_op;
    t[lex::token::BIT_AND_ASSIGN] = parsers::binary_op;
    t[lex::token::BIT_OR_ASSIGN] = parsers::binary_op;
    t[lex::token::XOR_ASSIGN] = parsers::binary_op;
    t[lex::token::LSHIFT_ASSIGN] = parsers::binary_op;
    t[lex::token::RSHIFT_ASSIGN] = parsers::binary_op;
    t[lex::token::EQ] = parsers::binary_op;
    t[lex::token::NE] = parsers::binary_op;
    t[lex::token::LT] = parsers::binary_op;
    t[lex::token::GT] = parsers::binary_op;
    t[lex::token::LTE] = parsers::binary_op;
    t[lex::token::GTE] = parsers::binary_op;

    // postfix-operators
    t[lex::token::OPTIONAL] = parsers::postfix_op;
    t[lex::token::INC] = parsers::postfix_op;
    t[lex::token::DEC] = parsers::postfix_op;

    return t;
})();

} // namespace fp::parse::detail
