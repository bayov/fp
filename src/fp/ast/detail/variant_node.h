#pragma once

#include <variant>

namespace fp::ast {

struct binary_op;
struct identifier;
struct number;

} // namespace fp::ast

namespace fp::ast::detail {

using variant_node = std::variant<
    binary_op,
    identifier,
    number
>;

} // namespace fp::ast::detail
