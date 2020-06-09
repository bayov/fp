#pragma once

#include <fp/syntax/ast/detail/base_node.h>
#include <fp/syntax/ast/node.h>

namespace fp::syntax::ast {

struct postfix_op : public detail::base_node<postfix_op> {
    node lhs;

    postfix_op(node lhs, lex::token_iterator op_token_it) :
        base_node(lhs.tokens().begin(), op_token_it + 1),
        lhs(std::move(lhs)),
        op_token_it(op_token_it)
    {}

    lex::token op() const { return op_token_it->token; }

    const fp::source_location& op_source_location() const {
        return op_token_it->source_location;
    }

private:
    lex::token_iterator op_token_it;
};

} // namespace fp::syntax::ast
