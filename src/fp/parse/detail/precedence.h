#pragma once

#include <fp/parse/detail/token_table_t.h>

namespace fp::parse::detail {

using precedence_t = size_t;

constexpr auto precedence_table_and_prefix = ([]() {
    precedence_t precedence = 0;
    auto t = token_table_t<precedence_t>::with_default(precedence);

    ++precedence;
    t[lex::token::SEMICOLON] = precedence;

    ++precedence;
    t[lex::token::COMMA] = precedence;

    ++precedence;
    t[lex::token::ASSIGN] = precedence;
    t[lex::token::PLUS_ASSIGN] = precedence;
    t[lex::token::MINUS_ASSIGN] = precedence;
    t[lex::token::MUL_ASSIGN] = precedence;
    t[lex::token::DIV_ASSIGN] = precedence;
    t[lex::token::MOD_ASSIGN] = precedence;
    t[lex::token::POW_ASSIGN] = precedence;
    t[lex::token::BIT_AND_ASSIGN] = precedence;
    t[lex::token::BIT_OR_ASSIGN] = precedence;
    t[lex::token::XOR_ASSIGN] = precedence;
    t[lex::token::LSHIFT_ASSIGN] = precedence;
    t[lex::token::RSHIFT_ASSIGN] = precedence;

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
    t[lex::token::LSHIFT] = precedence;
    t[lex::token::RSHIFT] = precedence;

    ++precedence;
    t[lex::token::PLUS] = precedence;
    t[lex::token::MINUS] = precedence;

    ++precedence;
    t[lex::token::MUL] = precedence;
    t[lex::token::DIV] = precedence;
    t[lex::token::MOD] = precedence;

    ++precedence;
    t[lex::token::POW] = precedence;

    ++precedence;
    auto prefix_precedence = precedence;     // all prefix operators

    ++precedence;
    t[lex::token::INC] = precedence;         // postfix increment
    t[lex::token::DEC] = precedence;         // postfix decrement
    t[lex::token::OPTIONAL] = precedence;
    t[lex::token::L_PAREN] = precedence;     // function call
    t[lex::token::L_BRACKET] = precedence;   // subscript
    t[lex::token::MEMBER_ACCESS] = precedence;

    ++precedence;
    t[lex::token::RANGE] = precedence;
    t[lex::token::CLOSED_RANGE] = precedence;

    ++precedence;
    t[lex::token::ERROR] = precedence;

    return std::make_pair(t, prefix_precedence);
})();

constexpr auto precedence_table = precedence_table_and_prefix.first;
constexpr precedence_t PREFIX_PRECEDENCE = precedence_table_and_prefix.second;

} // namespace fp::parse::detail
