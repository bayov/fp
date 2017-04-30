#pragma once

#include <memory>

#include <fp/common/source_location.h>
#include <fp/lex/token_view.h>

namespace fp::ast {

namespace detail { struct variant_node; }

using node = std::unique_ptr<detail::variant_node>;

/// The node's source-location.
const source_location& source(const node&);

/// The tokens that make up this node.
const lex::token_view& tokens(const node&);

template <class NodeType, class... Args>
node make(Args&& ... args) {
    return std::make_unique<detail::variant_node>(
        std::in_place_type<NodeType>,
        std::forward<Args>(args)...
    );
}

} // fp::ast

namespace std {

template <class T>
constexpr decltype(auto) get(const fp::ast::node& n) { return std::get<T>(*n); }

template <class Visitor>
constexpr decltype(auto) visit(Visitor&& visitor, const fp::ast::node& n) {
    return std::visit(visitor, *n);
}

} // std

#include <fp/ast/detail/variant_node.h>
