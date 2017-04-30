#pragma once

#include <fp/ast/node.h>
#include <fp/parse/detail/parser_state.h>
#include <fp/parse/detail/parsers/identifier.h>
#include <fp/parse/detail/parsers/integer.h>
#include <fp/parse/detail/parsers/prefix_op.h>
#include <fp/parse/detail/constexpr_token_table.h>

namespace fp::parse::detail {

using prefix_parser_t = ast::node (*)(parser_state&);

inline ast::node prefix_parser_error(parser_state& s) {
    s.error();
    assert(false);
}

using prefix_parser_table = constexpr_token_table<prefix_parser_t>
    ::set_default<prefix_parser_error>
    ::set<lex::token::IDENTIFIER, parsers::identifier>
    ::set<lex::token::INTEGER, parsers::integer>
    ::set<lex::token::DECORATOR, parsers::prefix_op>
    ::set<lex::token::BIT_NOT, parsers::prefix_op>
    ::set<lex::token::PLUS, parsers::prefix_op>
    ::set<lex::token::MINUS, parsers::prefix_op>
    ::set<lex::token::BIT_AND, parsers::prefix_op>
    ::set<lex::token::INC, parsers::prefix_op>
    ::set<lex::token::DEC, parsers::prefix_op>;

} // fp::parse::detail
