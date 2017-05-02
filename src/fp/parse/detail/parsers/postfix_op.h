#pragma once

#include <fp/ast/postfix_op.h>
#include <fp/parse/detail/parser_state.h>

namespace fp::parse::detail::parsers {

inline ast::node postfix_op(parser_state& p, ast::node lhs) {
    return ast::make<ast::postfix_op>(std::move(lhs), p.it++);
}

} // namespace fp::parse::detail::parsers
