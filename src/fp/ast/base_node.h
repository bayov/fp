#pragma once

#include <fp/common/source_location.h>
#include <fp/lex/token_view.h>

namespace fp::ast {

/// Common base of all AST nodes.
class base_node {
public:

    explicit base_node(lex::token_view tokens) :
        m_source(tokens),
        m_tokens(std::move(tokens))
    {}

    base_node(lex::token_iterator from, lex::token_iterator to) :
        base_node(lex::token_view(from, to))
    {}

    base_node(const base_node&) = delete;

    /// The node's source-location.
    const source_location& source() const { return m_source; }

    /// The tokens that make up this node.
    const lex::token_view& tokens() const { return m_tokens; }

private:

    source_location m_source;
    lex::token_view m_tokens;

};

} // namespace fp::ast
