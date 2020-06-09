#pragma once

#include <fp/syntax/detail/precedence.h>
#include <fp/syntax/detail/parsing_state.h>

namespace fp::syntax::detail {

/// Parses the next token as ast::prefix_op.
ast::node parse_prefix_op(parsing_state& s) {
    lex::token_iterator op = s.next++;
    return ast::prefix_op(op, s.parse(prefix_op_precedence));
}

} // namespace fp::syntax::detail
