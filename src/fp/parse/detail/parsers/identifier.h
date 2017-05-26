#pragma once

#include <fp/ast/identifier.h>
#include <fp/parse/detail/parser_state.h>

namespace fp::parse::detail::parsers {

inline ast::node identifier(parser_state& s) {
    return ast::make<ast::identifier>(s.it++);
}

} // namespace fp::parse::detail::parsers
