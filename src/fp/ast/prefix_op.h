#pragma once

#include "base_node.h"
#include "node.h"

namespace fp::ast {

class prefix_op : public base_node {
public:

    using op_t = lex::token;

    prefix_op(lex::token_iterator it, node rhs) :
        base_node(it, ast::tokens(rhs).end()),
        m_rhs(std::move(rhs))
    {}

    op_t op() const { return tokens().front().value; }
    const node& rhs() const { return m_rhs; }

    const input_view& op_symbols() const {
        return tokens().front().source.symbols;
    }

private:

    node m_rhs;

};

} // fp::ast
