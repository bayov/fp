#pragma once

#include <fp/ast/node.h>
#include <fp/parse/detail/parser_state.h>
#include <fp/parse/detail/parsers/binary_op.h>
#include <fp/parse/detail/parsers/postfix_op.h>
#include <fp/parse/detail/constexpr_token_table.h>

namespace fp::parse::detail {

using infix_parser_t = ast::node (*)(parser_state&, ast::node);

inline ast::node infix_parser_non_infix(parser_state& s, ast::node lhs) {
    return lhs;
}

using infix_parser_table = constexpr_token_table<infix_parser_t>
    ::set_default<infix_parser_non_infix>

    // binary-operators
    ::set<lex::token::COMMA, parsers::binary_op>
    ::set<lex::token::ANNOTATION, parsers::binary_op>
    ::set<lex::token::MEMBER_ACCESS, parsers::binary_op>
    ::set<lex::token::RANGE, parsers::binary_op>
    ::set<lex::token::CLOSED_RANGE, parsers::binary_op>
    ::set<lex::token::TYPE_ARROW, parsers::binary_op>
    ::set<lex::token::LAMBDA_ARROW, parsers::binary_op>
    ::set<lex::token::PLUS, parsers::binary_op>
    ::set<lex::token::MINUS, parsers::binary_op>
    ::set<lex::token::MUL, parsers::binary_op>
    ::set<lex::token::DIV, parsers::binary_op>
    ::set<lex::token::MOD, parsers::binary_op>
    ::set<lex::token::POW, parsers::binary_op>
    ::set<lex::token::BIT_AND, parsers::binary_op>
    ::set<lex::token::BIT_OR, parsers::binary_op>
    ::set<lex::token::XOR, parsers::binary_op>
    ::set<lex::token::LSHIFT, parsers::binary_op>
    ::set<lex::token::RSHIFT, parsers::binary_op>
    ::set<lex::token::ASSIGN, parsers::binary_op>
    ::set<lex::token::PLUS_ASSIGN, parsers::binary_op>
    ::set<lex::token::MINUS_ASSIGN, parsers::binary_op>
    ::set<lex::token::MUL_ASSIGN, parsers::binary_op>
    ::set<lex::token::DIV_ASSIGN, parsers::binary_op>
    ::set<lex::token::MOD_ASSIGN, parsers::binary_op>
    ::set<lex::token::POW_ASSIGN, parsers::binary_op>
    ::set<lex::token::BIT_AND_ASSIGN, parsers::binary_op>
    ::set<lex::token::BIT_OR_ASSIGN, parsers::binary_op>
    ::set<lex::token::XOR_ASSIGN, parsers::binary_op>
    ::set<lex::token::LSHIFT_ASSIGN, parsers::binary_op>
    ::set<lex::token::RSHIFT_ASSIGN, parsers::binary_op>
    ::set<lex::token::EQ, parsers::binary_op>
    ::set<lex::token::NE, parsers::binary_op>
    ::set<lex::token::LT, parsers::binary_op>
    ::set<lex::token::GT, parsers::binary_op>
    ::set<lex::token::LTE, parsers::binary_op>
    ::set<lex::token::GTE, parsers::binary_op>

    // postfix-operators
    ::set<lex::token::OPTIONAL, parsers::postfix_op>
    ::set<lex::token::INC, parsers::postfix_op>
    ::set<lex::token::DEC, parsers::postfix_op>;

} // fp::parse::detail
