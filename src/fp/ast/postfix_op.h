#pragma once

#include <fp/ast/base_node.h>
#include <fp/ast/node.h>

namespace fp::ast {

class postfix_op : public base_node {
public:

    using op_t = lex::token;

    postfix_op(node lhs, lex::token_iterator it) :
        base_node(ast::tokens(lhs).begin(), it + 1),
        m_lhs(std::move(lhs))
    {}

    op_t op() const { return tokens().back().value; }
    const node& lhs() const { return m_lhs; }

    const input_view& op_symbols() const {
        return tokens().back().source.symbols;
    }

private:

    node m_lhs;

};

} // fp::ast
