#pragma once

#include <fp/ast/prefix_op.h>
#include <fp/parse/detail/parser_state.h>

namespace fp::parse::detail::parsers {

inline ast::node prefix_op(parser_state& s) {
    return ast::make<ast::prefix_op>(s.it++, s.parse(PREFIX_PRECEDENCE));
}

} // namespace fp::parse::detail::parsers
