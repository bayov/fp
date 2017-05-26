#pragma once

#include <variant>

#include <fp/ast/base_node.h>
#include <fp/ast/error.h>
#include <fp/ast/empty.h>
#include <fp/ast/identifier.h>
#include <fp/ast/integer.h>
#include <fp/ast/binary_op.h>
#include <fp/ast/postfix_op.h>
#include <fp/ast/prefix_op.h>
#include <fp/ast/import.h>

namespace fp::ast::detail {

using variant_node_t = std::variant<
    error,
    empty,
    identifier,
    integer,
    binary_op,
    postfix_op,
    prefix_op,
    import
>;

struct variant_node : variant_node_t { using variant_node_t::variant; };

} // namespace fp::ast::detail
