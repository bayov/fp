#pragma once

#include <fp/lex/tokenized_list.h>
#include <fp/syntax/ast/node.h>

namespace fp::syntax::ast::detail {

/// Base class (CRTP) of all AST nodes.
template <class Derived>
struct base_node {
    explicit base_node(lex::tokenized_view tokens) :
        tokens_(std::move(tokens))
    {}

    base_node(lex::token_iterator from, lex::token_iterator to) :
        base_node(lex::tokenized_view(from, to))
    {}

    base_node(const base_node&) = delete;
    base_node(base_node&&) = default;

    lex::tokenized_view tokens() const { return tokens_; }

    const fp::source_location& source_location() const {
        if (!source_location_) {
            source_location_.emplace(get_source_location(tokens_));
        }
        return *source_location_;
    }

    operator node() const& {
        return node::make(std::move(static_cast<const Derived&>(*this)));
    }

    operator node() && {
        return node::make(std::move(static_cast<Derived&&>(*this)));
    }

private:
    lex::tokenized_view tokens_;
    mutable std::optional<fp::source_location> source_location_;
};

} // namespace fp::syntax::ast::detail
