#pragma once

#include <fp/syntax/ast/detail/base_node.h>

namespace fp::syntax::ast {

/**
 * A special node type that represents an empty AST.
 *
 * This node will never appear as a child of another AST node. For example, when
 * parsing `1 +`, ast::binary_op will contain an as::error as its RHS, and not
 * ast::empty.
 *
 * Note that since ast::empty::tokens() is an empty list, calling
 * ast::empty::source_location() will result in an exception being thrown.
 */
struct empty : detail::base_node<error> {
    using detail::base_node<error>::base_node;
};

} // namespace fp::syntax::ast
