#pragma once

#include <fp/ast/binary_op.h>

#include <fp/parse/detail/parser_state.h>

namespace fp::parse::detail::parsers {

inline ast::node binary_op(parser_state& p, ast::node lhs) {
    auto op = p.it++;
    ast::node rhs = p.parse(p.precedence(op));
    return ast::make<ast::binary_op>(std::move(lhs), op, std::move(rhs));
}

} // fp::parse::detail::parsers
