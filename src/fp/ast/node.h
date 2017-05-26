#pragma once

#include <memory>

#include <fp/util/box.h>
#include <fp/util/match.h>
#include <fp/common/source_location.h>
#include <fp/lex/token_view.h>
#include "base_node.h"

namespace fp::ast {

namespace detail { struct variant_node; }

class node : public util::box<detail::variant_node> {
public:

    using util::box<detail::variant_node>::box;

    /// @return The node's source-location.
    const source_location& source() const;

    /// @return The tokens that make up this node.
    const lex::token_view& tokens() const;

    template <class NodeType>
    const bool is() const {
        return std::holds_alternative<NodeType>(as_variant());
    }

    /// Match over the node (using util::match).
    template <class... Fs>
    decltype(auto) match(Fs&&... fs) const {
        return util::match(as_variant())(std::forward<Fs>(fs)...);
    }

    /// Visit the node using the given visitor (using std::visit).
    template <class Visitor>
    decltype(auto) visit(Visitor&& visitor) const {
        return std::visit(visitor, as_variant());
    }

private:

    const base_node& as_base() const;
    const detail::variant_node& as_variant() const { return *this; }

};

/// Construct an AST node of type `NodeType`.
template <class NodeType, class... Args>
node make(Args&& ... args) {
    return node(std::in_place_type<NodeType>, std::forward<Args>(args)...);
}

} // namespace fp::ast

#include <fp/ast/detail/variant_node.h>
