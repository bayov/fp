#pragma once

#include <fp/common/source_origin.h>

#include <fp/lex/token_view.h>

namespace fp::ast {

/// Common base of all AST nodes.
class base_node {
public:

    explicit base_node(lex::token_view tokens) :
        m_origin(tokens),
        m_tokens(std::move(tokens))
    {}

    base_node(lex::token_iterator from, lex::token_iterator to) :
        base_node(lex::token_view(from, to))
    {}

    /// The origin of the node inside the source code.
    const source_origin& origin() const { return m_origin; }

    /// The tokens that make up this node.
    const lex::token_view& tokens() const { return m_tokens; }

private:

    source_origin m_origin;
    lex::token_view m_tokens;

};

} // fp::ast
