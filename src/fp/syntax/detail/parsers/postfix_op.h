#pragma once

#include <fp/syntax/detail/parsing_state.h>

namespace fp::syntax::detail {

/// Parses the next token as an ast::binary_op.
ast::node parse_postfix_op(parsing_state& s, ast::node lhs) {
    lex::token_iterator op = s.next++;
    return ast::postfix_op(std::move(lhs), op);
}

} // namespace fp::syntax::detail
