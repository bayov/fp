#pragma once

#include <fp/lex/token.h>
#include <fp/lex/token_view.h>

#include "base_node.h"
#include "node.h"

namespace fp::ast {

class binary_op : public base_node {
public:

    using op_t = lex::token;

    binary_op(node lhs, lex::token_iterator it, node rhs) :
        base_node(ast::tokens(lhs).begin(), ast::tokens(rhs).end()),
        m_lhs(std::move(lhs)),
        m_op(it),
        m_rhs(std::move(rhs))
    {}

    op_t op() const { return m_op->value; }
    const node& lhs() const { return m_lhs; }
    const node& rhs() const { return m_rhs; }

    const input_view& op_symbols() const { return m_op->source.symbols; }

private:

    node m_lhs;
    lex::token_iterator m_op;
    node m_rhs;

};

} // fp::ast
