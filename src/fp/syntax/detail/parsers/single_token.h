#pragma once

#include <fp/syntax/detail/parsing_state.h>

namespace fp::syntax::detail {

/// Parses the next token as an AST node of the given `Node` type.
template <class Node>
ast::node parse_single_token(parsing_state& s) { return Node(s.next++); }

} // namespace fp::syntax::detail
