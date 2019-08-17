#pragma once

#include <variant>
#include <memory>

#include <fp/util/overloaded.h>
#include <fp/lex/tokenized_list.h>
#include <fp/syntax/ast/detail/variant_node.h>

namespace fp::syntax::ast {

/**
 * Represents an AST node.
 *
 * An AST can be produced from by calling syntax::parse.
 */
struct node {
    template <class NodeType>
    static node make(NodeType&& n) {
        return node(std::make_unique<detail::variant_node>(
            std::forward<NodeType>(n)
        ));
    }

    /// Returns the tokens that this node originates from.
    lex::tokenized_view tokens() const;

    /// Returns the location of this node in the source code.
    const fp::source_location& source_location() const;

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

    explicit node(std::unique_ptr<detail::variant_node>);

    // delays evaluation of the incomplete type detail::variant_node
    template <class N = node>
    const detail::variant_node& get_variant() const {
        return *((const N&)(*this)).variant_node;
    }
};

} // namespace fp::syntax::ast

// all node types must be included here to ensure that detail::variant_node
// becomes a complete type
#include <fp/syntax/ast/types/binary_op.inl>
#include <fp/syntax/ast/types/empty.inl>
#include <fp/syntax/ast/types/error.inl>
#include <fp/syntax/ast/types/identifier.inl>
#include <fp/syntax/ast/types/if.inl>
#include <fp/syntax/ast/types/infix_error.inl>
#include <fp/syntax/ast/types/number.inl>
#include <fp/syntax/ast/types/postfix_op.inl>
#include <fp/syntax/ast/types/prefix_op.inl>

static_assert(
    sizeof(fp::syntax::ast::detail::variant_node) > 0,
    "The definition of the variant must be complete (include all node types)"
);
