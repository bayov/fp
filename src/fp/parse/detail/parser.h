#pragma once

#include <fp/lex/token_view.h>
#include <fp/ast/node.h>
#include <fp/parse/detail/precedence.h>
#include <fp/parse/detail/prefix_parser.h>
#include <fp/parse/detail/infix_parser.h>

namespace fp::parse::detail {

class parser {
public:

    parser() : m_state(*this) {}

    ast::node parse(const lex::token_view& tokens) {
        m_state.initialize(tokens);
        ast::node result = parse(0);
        if (m_state.it != m_state.end) { m_state.error(); }
        return result;
    }

private:

    parser_state m_state;

    precedence_t precedence() const { return precedence(m_state.it); }

    precedence_t precedence(lex::token_iterator it) const {
        return precedence(it->value);
    }

    precedence_t precedence(lex::token t) const { return precedence_table[t]; }

    ast::node parse(precedence_t p) {
        ast::node lhs = prefix_parser_table[m_state.it->value](m_state);
        while (p < precedence_table[m_state.it->value]) {
            lhs = infix_parser_table[m_state.it->value](m_state, std::move(lhs));
        }
        return lhs;
    }

    friend class parser_state;

};

} // namespace fp::parse::detail
