#pragma once

#include <fp/ast/base_node.h>
#include <fp/ast/node.h>

namespace fp::ast {

class prefix_op : public base_node {
public:

    using op_t = lex::token;

    prefix_op(lex::token_iterator it, node rhs) :
        base_node(it, rhs.tokens().end()),
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

} // namespace fp::ast
