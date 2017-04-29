#pragma once

#include <fp/ast/integer.h>

#include <fp/parse/detail/parser_state.h>

namespace fp::parse::detail::parsers {

inline ast::node integer(parser_state& p) {
    return ast::make<ast::integer>(p.it++);
}

} // fp::parse::detail::parsers
