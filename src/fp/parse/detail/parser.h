#pragma once

#include <fp/lex/token_view.h>

#include <fp/ast/node.h>

#include "prefix_parser.h"
#include "infix_parser.h"

namespace fp::parse::detail {

class parser {
public:

    parser() : m_state(*this) {}

    ast::node parse(const lex::token_view& tokens) {
        m_state.initialize(tokens);
        return parse();
    }

private:

    parser_state m_state;

    prefix_parser_t prefix_parser() const {
        return prefix_parser_table::get(m_state.it->value);
    }

    infix_parser_t infix_parser() const {
        return infix_parser_table::get(m_state.it->value);
    }

    ast::node parse() {
        ast::node lhs = prefix_parser()(m_state);
        return infix_parser()(m_state, std::move(lhs));
    }

    friend class parser_state;

};

} // fp::parse::detail
