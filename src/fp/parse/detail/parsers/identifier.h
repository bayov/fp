#pragma once

#include <fp/ast/identifier.h>
#include <fp/parse/detail/parser_state.h>

namespace fp::parse::detail::parsers {

inline ast::node identifier(parser_state& p) {
    return ast::make<ast::identifier>(p.it++);
}

} // namespace fp::parse::detail::parsers
