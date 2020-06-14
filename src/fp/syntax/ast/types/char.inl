#pragma once

#include <fp/syntax/ast/detail/base_node.h>

namespace fp::syntax::ast {

/// Represents a character literal.
struct char_ : detail::base_node<char_> {
    char_t value;

    explicit char_(lex::token_iterator token_it) :
        base_node(token_it, token_it + 1),
        value(token_it->get_attribute<lex::token::CHAR>())
    {}
};

} // namespace fp::syntax::ast
