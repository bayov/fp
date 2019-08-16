#pragma once

#include <fp/syntax/ast/detail/base_node.h>
#include <fp/syntax/ast/node.h>

namespace fp::syntax::ast {

struct prefix_op : public detail::base_node<prefix_op> {
    node rhs;
    
    prefix_op(lex::token_iterator op_token_it, node rhs) :
        base_node(op_token_it, rhs.tokens().end()),
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
