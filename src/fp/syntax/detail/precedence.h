#pragma once

#include <fp/syntax/detail/token_table_t.h>

namespace fp::syntax::detail {

/**
 * Represents an operator's precedence.
 *
 * Higher precedence means that an operator will be resolved earlier in an
 * expression. For example, in the expression `1 + 2 * 3`, operator `*` will be
 * parsed into an ast::node before operator `+`, since the precedence of
 * token::MUL is higher than that of token::ADD.
 */
using precedence_t = size_t;

constexpr auto precedence_table = token_table_t<precedence_t>([](auto& t) {
    precedence_t precedence = 0;
    t.set_default(precedence);

    ++precedence;
    t[lex::token::SEMICOLON] = precedence;

    ++precedence;
    t[lex::token::COMMA] = precedence;

    ++precedence;
    t[lex::token::ASSIGN] = precedence;
    t[lex::token::ADD_ASSIGN] = precedence;
    t[lex::token::SUB_ASSIGN] = precedence;
    t[lex::token::MUL_ASSIGN] = precedence;
    t[lex::token::DIV_ASSIGN] = precedence;
    t[lex::token::MOD_ASSIGN] = precedence;
    t[lex::token::POW_ASSIGN] = precedence;
    t[lex::token::BIT_AND_ASSIGN] = precedence;
    t[lex::token::BIT_OR_ASSIGN] = precedence;
    t[lex::token::XOR_ASSIGN] = precedence;
    t[lex::token::SHL_ASSIGN] = precedence;
    t[lex::token::SHR_ASSIGN] = precedence;

    ++precedence;
    t[lex::token::TYPE_ARROW] = precedence;
    t[lex::token::LAMBDA_ARROW] = precedence;

    ++precedence;
    t[lex::token::ANNOTATION] = precedence;

    ++precedence;
    t[lex::token::OR] = precedence;

    ++precedence;
    t[lex::token::AND] = precedence;

    ++precedence;
    t[lex::token::BIT_OR] = precedence;

    ++precedence;
    t[lex::token::XOR] = precedence;

    ++precedence;
    t[lex::token::BIT_AND] = precedence;

    ++precedence;
    t[lex::token::EQ] = precedence;
    t[lex::token::NE] = precedence;

    ++precedence;
    t[lex::token::LT] = precedence;
    t[lex::token::GT] = precedence;
    t[lex::token::LTE] = precedence;
    t[lex::token::GTE] = precedence;

    ++precedence;
    t[lex::token::SHL] = precedence;
    t[lex::token::SHR] = precedence;

    ++precedence;
    t[lex::token::ADD] = precedence;
    t[lex::token::SUB] = precedence;

    ++precedence;
    t[lex::token::MUL] = precedence;
    t[lex::token::DIV] = precedence;
    t[lex::token::MOD] = precedence;

    ++precedence;
    t[lex::token::POW] = precedence;

    ++precedence;
    // all prefix operators will be represented by this token
    t[lex::token::NOT] = precedence;

    ++precedence;
    t[lex::token::RANGE] = precedence;
    t[lex::token::CLOSED_RANGE] = precedence;

    ++precedence;
    t[lex::token::INC] = precedence;       // postfix increment
    t[lex::token::DEC] = precedence;       // postfix decrement
    t[lex::token::OPTIONAL] = precedence;
    t[lex::token::L_PAREN] = precedence;   // function call
    t[lex::token::L_BRACKET] = precedence; // subscript
    t[lex::token::MEMBER_ACCESS] = precedence;

    ++precedence;
    t[lex::token::SCOPE] = precedence;

    ++precedence;
    t[lex::token::ERROR] = precedence;
});

/**
 * The precedence of all prefix operators.
 *
 * This includes operators which can act as both prefix and infix operators,
 * such as token::ADD:
 * ~~~
 * +42    ---> operator `+` has precedence value: prefix_op_precedence
 * 1 + 2  ---> operator `+` has precedence value: precedence_table[token::ADD]
 * ~~~
 */
constexpr precedence_t prefix_op_precedence = precedence_table[lex::token::NOT];

} // namespace fp::syntax::detail
