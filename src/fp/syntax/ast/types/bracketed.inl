#pragma once

#include <vector>

#include <fp/syntax/ast/detail/base_node.h>
#include <fp/syntax/ast/node.h>

namespace fp::syntax::ast {

/**
 * A bracketed ast::node consists of the opening bracket token, closing bracket
 * token, and the enclosed node.
 *
 * There are three types of brackets:
 *  - parentheses, `(...)`, using token::L_PAREN and token::R_PAREN.
 *  - square-brackets, `[...]`, using token::L_BRACKET and token::R_BRACKET.
 *  - curly-bracers, `{...}`, using token::L_BRACE and token::R_BRACE.
 */
struct bracketed : public detail::base_node<bracketed> {
    lex::token_iterator opening_token;
    lex::token_iterator closing_token;
    node enclosed_node;

    bracketed(
        lex::token_iterator opening_token,
        lex::token_iterator closing_token,
        node enclosed_node
    ) :
        base_node(opening_token, closing_token + 1),
        enclosed_node(std::move(enclosed_node))
    {}
};

} // namespace fp::syntax::ast
