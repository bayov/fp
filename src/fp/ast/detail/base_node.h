#pragma once

#include <fp/lex/tokenized_list.h>

namespace fp::ast::detail {

/// Base class of all AST nodes.
struct base_node {
    fp::source_location source_location;
    lex::tokenized_view tokens;

    explicit base_node(lex::tokenized_view tokens) :
        source_location(get_source_location(tokens)),
        tokens(std::move(tokens))
    {}

    base_node(lex::token_iterator from, lex::token_iterator to) :
        base_node(lex::tokenized_view(from, to))
    {}

    base_node(const base_node&) = delete;
    base_node(base_node&&) = default;
};

} // namespace fp::ast::detail
