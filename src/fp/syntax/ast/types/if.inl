#pragma once

#include <fp/syntax/ast/detail/base_node.h>
#include <fp/syntax/ast/node.h>

namespace fp::syntax::ast {

struct if_ : public detail::base_node<if_> {
    node condition;
    node body;

    if_(lex::token_iterator if_token_it, node condition, node body) :
        base_node(if_token_it, body.tokens().end()),
        condition(std::move(condition)),
        body(std::move(body))
    {}
};

} // namespace fp::syntax::ast
