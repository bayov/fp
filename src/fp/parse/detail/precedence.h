#pragma once

#include <boost/preprocessor/slot/counter.hpp>

#include "constexpr_token_table.h"

namespace fp::parse::detail {

using precedence_t = size_t;

constexpr precedence_t STARTING_PRECEDENCE = BOOST_PP_COUNTER;
#define FP_PRECEDENCE() (BOOST_PP_COUNTER - STARTING_PRECEDENCE)

using precedence_table = constexpr_token_table<precedence_t>
    ::set_default<FP_PRECEDENCE()>

#include BOOST_PP_UPDATE_COUNTER()
    ::set<lex::token::SEMICOLON, FP_PRECEDENCE()>

#include BOOST_PP_UPDATE_COUNTER()
    ::set<lex::token::COMMA, FP_PRECEDENCE()>

#include BOOST_PP_UPDATE_COUNTER()
    ::set<lex::token::ASSIGN, FP_PRECEDENCE()>
    ::set<lex::token::PLUS_ASSIGN, FP_PRECEDENCE()>
    ::set<lex::token::MINUS_ASSIGN, FP_PRECEDENCE()>
    ::set<lex::token::MUL_ASSIGN, FP_PRECEDENCE()>
    ::set<lex::token::DIV_ASSIGN, FP_PRECEDENCE()>
    ::set<lex::token::MOD_ASSIGN, FP_PRECEDENCE()>
    ::set<lex::token::POW_ASSIGN, FP_PRECEDENCE()>
    ::set<lex::token::BIT_AND_ASSIGN, FP_PRECEDENCE()>
    ::set<lex::token::BIT_OR_ASSIGN, FP_PRECEDENCE()>
    ::set<lex::token::XOR_ASSIGN, FP_PRECEDENCE()>
    ::set<lex::token::LSHIFT_ASSIGN, FP_PRECEDENCE()>
    ::set<lex::token::RSHIFT_ASSIGN, FP_PRECEDENCE()>

#include BOOST_PP_UPDATE_COUNTER()
    ::set<lex::token::TYPE_ARROW, FP_PRECEDENCE()>
    ::set<lex::token::LAMBDA_ARROW, FP_PRECEDENCE()>

#include BOOST_PP_UPDATE_COUNTER()
    ::set<lex::token::COLON, FP_PRECEDENCE()>       // (type) annotation

#include BOOST_PP_UPDATE_COUNTER()
    ::set<lex::token::OR, FP_PRECEDENCE()>

#include BOOST_PP_UPDATE_COUNTER()
    ::set<lex::token::AND, FP_PRECEDENCE()>

#include BOOST_PP_UPDATE_COUNTER()
    ::set<lex::token::BIT_OR, FP_PRECEDENCE()>

#include BOOST_PP_UPDATE_COUNTER()
    ::set<lex::token::XOR, FP_PRECEDENCE()>

#include BOOST_PP_UPDATE_COUNTER()
    ::set<lex::token::BIT_AND, FP_PRECEDENCE()>

#include BOOST_PP_UPDATE_COUNTER()
    ::set<lex::token::EQ, FP_PRECEDENCE()>
    ::set<lex::token::NE, FP_PRECEDENCE()>

#include BOOST_PP_UPDATE_COUNTER()
    ::set<lex::token::LT, FP_PRECEDENCE()>
    ::set<lex::token::GT, FP_PRECEDENCE()>
    ::set<lex::token::LTE, FP_PRECEDENCE()>
    ::set<lex::token::GTE, FP_PRECEDENCE()>

#include BOOST_PP_UPDATE_COUNTER()
    ::set<lex::token::LSHIFT, FP_PRECEDENCE()>
    ::set<lex::token::RSHIFT, FP_PRECEDENCE()>

#include BOOST_PP_UPDATE_COUNTER()
    ::set<lex::token::PLUS, FP_PRECEDENCE()>
    ::set<lex::token::MINUS, FP_PRECEDENCE()>

#include BOOST_PP_UPDATE_COUNTER()
    ::set<lex::token::MUL, FP_PRECEDENCE()>
    ::set<lex::token::DIV, FP_PRECEDENCE()>
    ::set<lex::token::MOD, FP_PRECEDENCE()>

#include BOOST_PP_UPDATE_COUNTER()
    ::set<lex::token::POW, FP_PRECEDENCE()>

#include BOOST_PP_UPDATE_COUNTER()
    // <reserved> : all prefix operators

#include BOOST_PP_UPDATE_COUNTER()
    ::set<lex::token::INC, FP_PRECEDENCE()>         // postfix increment
    ::set<lex::token::DEC, FP_PRECEDENCE()>         // postfix decrement
    ::set<lex::token::OPTIONAL, FP_PRECEDENCE()>
    ::set<lex::token::L_PAREN, FP_PRECEDENCE()>     // function call
    ::set<lex::token::L_BRACKET, FP_PRECEDENCE()>   // subscript
    ::set<lex::token::PERIOD, FP_PRECEDENCE()>      // member access

#include BOOST_PP_UPDATE_COUNTER()
    ::set<lex::token::RANGE, FP_PRECEDENCE()>
    ::set<lex::token::CLOSED_RANGE, FP_PRECEDENCE()>;

constexpr precedence_t PREFIX_PRECEDENCE =
    precedence_table::get<lex::token::INC>() - 1;

} // fp::parse::detail
