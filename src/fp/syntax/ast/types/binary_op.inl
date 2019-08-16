#pragma once

#include <fp/syntax/ast/detail/base_node.h>
#include <fp/syntax/ast/node.h>

namespace fp::syntax::ast {

struct binary_op : public detail::base_node<binary_op> {
    node lhs;
    node rhs;
    
    binary_op(lex::token_iterator op_token_it, node lhs, node rhs) :
        base_node(lhs.tokens().begin(), rhs.tokens().end()),
        lhs(std::move(lhs)),
        rhs(std::move(rhs)),
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
