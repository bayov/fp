#pragma once

#include <fp/ast/binary_op.h>
#include <fp/parse/detail/token_table_t.h>
#include <fp/parse/detail/parser_state.h>

namespace fp::parse::detail::parsers {

enum class associativity { LEFT, RIGHT };

constexpr auto associativity_table = ([]() {
    auto t = token_table_t<associativity>::with_default(associativity::LEFT);
    t[lex::token::ANNOTATION] = associativity::RIGHT;
    t[lex::token::POW] = associativity::RIGHT;
    t[lex::token::TYPE_ARROW] = associativity::RIGHT;
    t[lex::token::LAMBDA_ARROW] = associativity::RIGHT;
    t[lex::token::ASSIGN] = associativity::RIGHT;
    t[lex::token::PLUS_ASSIGN] = associativity::RIGHT;
    t[lex::token::MINUS_ASSIGN] = associativity::RIGHT;
    t[lex::token::MUL_ASSIGN] = associativity::RIGHT;
    t[lex::token::DIV_ASSIGN] = associativity::RIGHT;
    t[lex::token::MOD_ASSIGN] = associativity::RIGHT;
    t[lex::token::POW_ASSIGN] = associativity::RIGHT;
    t[lex::token::BIT_AND_ASSIGN] = associativity::RIGHT;
    t[lex::token::BIT_OR_ASSIGN] = associativity::RIGHT;
    t[lex::token::XOR_ASSIGN] = associativity::RIGHT;
    t[lex::token::LSHIFT_ASSIGN] = associativity::RIGHT;
    t[lex::token::RSHIFT_ASSIGN] = associativity::RIGHT;
    return t;
})();

inline ast::node binary_op(parser_state& s, ast::node lhs) {
    auto op = s.it++;
    precedence_t p = precedence_table[op->value];
    p = associativity_table[op->value] == associativity::RIGHT ? p - 1 : p;
    ast::node rhs = s.parse(p);
    return ast::make<ast::binary_op>(std::move(lhs), op, std::move(rhs));
}

} // namespace fp::parse::detail::parsers
