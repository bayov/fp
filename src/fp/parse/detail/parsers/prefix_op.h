#pragma once

#include <fp/ast/prefix_op.h>
#include <fp/parse/detail/parser_state.h>

namespace fp::parse::detail::parsers {

inline ast::node prefix_op(parser_state& p) {
    return ast::make<ast::prefix_op>(p.it++, p.parse(PREFIX_PRECEDENCE));
}

} // namespace fp::parse::detail::parsers
