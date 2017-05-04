#pragma once

#include <fp/ast/node.h>
#include <fp/parse/detail/parser_state.h>
#include <fp/parse/detail/token_table_t.h>
#include <fp/parse/detail/parsers/identifier.h>
#include <fp/parse/detail/parsers/integer.h>
#include <fp/parse/detail/parsers/prefix_op.h>

namespace fp::parse::detail {

using prefix_parser_t = ast::node (*)(parser_state&);

inline ast::node prefix_parser_error(parser_state& s) {
    s.error();
    throw std::invalid_argument("");
}

constexpr auto prefix_parser_table = ([]() {
    auto t = token_table_t<prefix_parser_t>::with_default(prefix_parser_error);
    t[lex::token::IDENTIFIER] = parsers::identifier;
    t[lex::token::INTEGER] = parsers::integer;
    t[lex::token::DECORATOR] = parsers::prefix_op;
    t[lex::token::BIT_NOT] = parsers::prefix_op;
    t[lex::token::PLUS] = parsers::prefix_op;
    t[lex::token::MINUS] = parsers::prefix_op;
    t[lex::token::BIT_AND] = parsers::prefix_op;
    t[lex::token::INC] = parsers::prefix_op;
    t[lex::token::DEC] = parsers::prefix_op;
    return t;
})();

} // namespace fp::parse::detail
