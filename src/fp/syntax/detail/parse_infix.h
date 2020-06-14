#pragma once

#include <fp/syntax/detail/parsing_state.h>
#include <fp/syntax/detail/token_table_t.h>
#include <fp/syntax/detail/parse_prefix.h>
#include <fp/syntax/detail/parsers/binary_op.h>
#include <fp/syntax/detail/parsers/postfix_op.h>
#include <fp/syntax/detail/parsers/sequence.h>

namespace fp::syntax::detail {

using infix_parser_t = ast::node (*)(parsing_state&, ast::node lhs);

/// Parses the next token as an ast::infix_error.
inline ast::node parse_infix_error(parsing_state& s, ast::node lhs) {
    s.report_error("unexpected token")
        .add_primary(s.next->source_location)
        .add_contextual(lhs.source_location());
    ++s.next;
    return ast::infix_error(std::move(lhs), s.next - 1);
}

constexpr auto infix_parser_table = token_table_t<infix_parser_t>([](auto& t) {
     t.set_default(parse_infix_error);

    // binary-operators
    t[lex::token::SEMICOLON]      = parse_sequence;
    t[lex::token::COMMA]          = parse_sequence;
    t[lex::token::ANNOTATION]     = parse_binary_op;
    t[lex::token::SCOPE]          = parse_binary_op;
    t[lex::token::MEMBER_ACCESS]  = parse_binary_op;
    t[lex::token::RANGE]          = parse_binary_op;
    t[lex::token::CLOSED_RANGE]   = parse_binary_op;
    t[lex::token::TYPE_ARROW]     = parse_binary_op;
    t[lex::token::LAMBDA_ARROW]   = parse_binary_op;
    t[lex::token::ADD]            = parse_binary_op;
    t[lex::token::SUB]            = parse_binary_op;
    t[lex::token::MUL]            = parse_binary_op;
    t[lex::token::DIV]            = parse_binary_op;
    t[lex::token::MOD]            = parse_binary_op;
    t[lex::token::POW]            = parse_binary_op;
    t[lex::token::BIT_AND]        = parse_binary_op;
    t[lex::token::BIT_OR]         = parse_binary_op;
    t[lex::token::XOR]            = parse_binary_op;
    t[lex::token::SHL]            = parse_binary_op;
    t[lex::token::SHR]            = parse_binary_op;
    t[lex::token::ASSIGN]         = parse_binary_op;
    t[lex::token::ADD_ASSIGN]     = parse_binary_op;
    t[lex::token::SUB_ASSIGN]     = parse_binary_op;
    t[lex::token::MUL_ASSIGN]     = parse_binary_op;
    t[lex::token::DIV_ASSIGN]     = parse_binary_op;
    t[lex::token::MOD_ASSIGN]     = parse_binary_op;
    t[lex::token::POW_ASSIGN]     = parse_binary_op;
    t[lex::token::BIT_AND_ASSIGN] = parse_binary_op;
    t[lex::token::BIT_OR_ASSIGN]  = parse_binary_op;
    t[lex::token::XOR_ASSIGN]     = parse_binary_op;
    t[lex::token::SHL_ASSIGN]     = parse_binary_op;
    t[lex::token::SHR_ASSIGN]     = parse_binary_op;
    t[lex::token::EQ]             = parse_binary_op;
    t[lex::token::NE]             = parse_binary_op;
    t[lex::token::LT]             = parse_binary_op;
    t[lex::token::GT]             = parse_binary_op;
    t[lex::token::LTE]            = parse_binary_op;
    t[lex::token::GTE]            = parse_binary_op;

    // postfix-operators
    t[lex::token::OPTIONAL] = parse_postfix_op;
    t[lex::token::INC]      = parse_postfix_op;
    t[lex::token::DEC]      = parse_postfix_op;

//    // error
//    t[lex::token::ERROR] = infix_parser_skip_error;
});

inline ast::node parse_infix(parsing_state& s, ast::node lhs) {
    return infix_parser_table[s.next->token](s, std::move(lhs));
}

} // namespace fp::syntax::detail
