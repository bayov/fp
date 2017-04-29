#pragma once

#include <fp/ast/binary_op.h>

#include <fp/parse/detail/parser_state.h>

namespace fp::parse::detail::parsers {

inline ast::node binary_op(parser_state& p, ast::node lhs) {
    return ast::make<ast::binary_op>(std::move(lhs), p.it++, p.parse());
}

} // fp::parse::detail::parsers
