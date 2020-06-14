#pragma once

#include <variant>

namespace fp::syntax::ast {

/* all AST node types need to be forward-declared here, and then they have to be
 * added to the detail::variant_node type below.
 *
 * They also have to be `#include`ed at the end of the ast/node.h file.
 *
 * Yes, 3 different places. All for the sake of a sleek user interface.
 *
 * Please keep the 3 lists lexicographically ordered.
 */
struct binary_op;
struct char_;
struct empty;
struct error;
struct identifier;
struct if_;
struct infix_error;
struct number;
struct postfix_op;
struct prefix_op;

} // namespace fp::syntax::ast

namespace fp::syntax::ast::detail {

using variant_node = std::variant<
    binary_op,
    char_,
    empty,
    error,
    identifier,
    if_,
    infix_error,
    number,
    postfix_op,
    prefix_op
>;

} // namespace fp::syntax::ast::detail
