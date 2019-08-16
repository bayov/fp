#pragma once

#include <fp/syntax/detail/token_table_t.h>
#include <fp/syntax/detail/parsing_state.h>
#include <fp/syntax/detail/precedence.h>

namespace fp::syntax::detail {

enum class associativity { LEFT, RIGHT };

constexpr auto associativity_table = token_table_t<associativity>([](auto& t) {
    t.set_default(associativity::LEFT);
    t[lex::token::ANNOTATION] = associativity::RIGHT;
    t[lex::token::POW] = associativity::RIGHT;
    t[lex::token::TYPE_ARROW] = associativity::RIGHT;
    t[lex::token::LAMBDA_ARROW] = associativity::RIGHT;
    t[lex::token::ASSIGN] = associativity::RIGHT;
    t[lex::token::ADD_ASSIGN] = associativity::RIGHT;
    t[lex::token::SUB_ASSIGN] = associativity::RIGHT;
    t[lex::token::MUL_ASSIGN] = associativity::RIGHT;
    t[lex::token::DIV_ASSIGN] = associativity::RIGHT;
    t[lex::token::MOD_ASSIGN] = associativity::RIGHT;
    t[lex::token::POW_ASSIGN] = associativity::RIGHT;
    t[lex::token::BIT_AND_ASSIGN] = associativity::RIGHT;
    t[lex::token::BIT_OR_ASSIGN] = associativity::RIGHT;
    t[lex::token::XOR_ASSIGN] = associativity::RIGHT;
    t[lex::token::SHL_ASSIGN] = associativity::RIGHT;
    t[lex::token::SHR_ASSIGN] = associativity::RIGHT;
    return t;
});

/// Parses the next token as an ast::binary_op.
ast::node parse_binary_op(parsing_state& s, ast::node lhs) {
    lex::token_iterator op = s.next++;
    precedence_t p = precedence_table[op->token];
    if (associativity_table[op->token] == associativity::RIGHT) { --p; }
    ast::node rhs = s.parse(p);
    return ast::binary_op(op, std::move(lhs), std::move(rhs));
}

} // namespace fp::syntax::detail
