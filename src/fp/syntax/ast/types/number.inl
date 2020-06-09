#pragma once

#include <fp/syntax/ast/detail/base_node.h>

namespace fp::syntax::ast {

struct number : detail::base_node<number> {
    source_view chars;

    explicit number(lex::token_iterator token_it) :
        base_node(token_it, token_it + 1),
        chars(token_it->get_attribute<lex::token::NUMBER>())
    {}
};

} // namespace fp::syntax::ast
