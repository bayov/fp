#pragma once

#include <fp/syntax/ast/detail/base_node.h>

namespace fp::syntax::ast {

/// Represents a syntax analysis error.
struct error : detail::base_node<error> {
    using detail::base_node<error>::base_node;
};

} // namespace fp::syntax::ast
