#pragma once

#include <variant>
#include <memory>

#include <fp/util/overloaded.h>
#include <fp/ast/detail/base_node.h>
#include <fp/ast/detail/variant_node.h>

namespace fp::ast {

/**
 * Represents an AST node.
 *
 * An AST can be produced from by calling syntax::parse.
 */
struct node {
    /// Returns the location of this node in the source code.
    const fp::source_location& source_location() const;

    /// Returns the tokens that this node originates from.
    const lex::tokenized_view& tokens() const;

    /// Returns true if this node is of the given type (e.g. ast::identifier).
    template <class NodeType>
    const bool is() const {
        return std::holds_alternative<NodeType>(get_variant());
    }

    //@{
    /**
     * Apply the given `visitor` on the node.
     *
     * ~~~{.cpp}
     * struct my_visitor {
     *     void operator()(const ast::identifier& identifier) const {
     *         std::cout << "identifier " << identifier.chars << std::endl;
     *     }
     *
     *     void operator()(const ast::binary_op& bin_op) const {
     *         std::cout << "binary-operation " << bin_op.op << std::endl;
     *         bin_op.lhs.visit(*this);
     *         bin_op.rhs.visit(*this);
     *     }
     *
     *     template <class Node>
     *     void operator()(const Node& node) const {
     *         std::cout << "some other AST node" << std::endl;
     *     }
     * };
     *
     * node.visit(my_visitor{});
     *
     * // multiple visitors can be given and overloaded
     * int n = node.visit(
     *     [](const ast::number&   ) { return 1; },
     *     [](const ast::binary_op&) { return 2; },
     *     [](const auto&          ) { return 3; } // default catch-all
     * );
     * ~~~
     */
    template <class Visitor>
    decltype(auto) visit(Visitor&& visitor) const {
        return std::visit(visitor, get_variant());
    }
    template <class... Visitors>
    decltype(auto) visit(Visitors&&... visitors) const {
        return visit(util::overloaded { std::forward<Visitors>(visitors)... });
    }
    //@}

private:
    std::unique_ptr<detail::variant_node> variant_node;

    // delays evaluation of the incomplete type detail::variant_node
    template <class N = node>
    const detail::variant_node& get_variant() const {
        return *((const N&)(*this)).variant_node;
    }

    const detail::base_node& get_base_node() const;
};

} // namespace fp::ast

// all node types must be included here to ensure that detail::variant_node
// becomes a complete type
#include <fp/ast/types/binary_op.h>
#include <fp/ast/types/identifier.h>
#include <fp/ast/types/number.h>
