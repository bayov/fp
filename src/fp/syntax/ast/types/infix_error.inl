#pragma once

#include <fp/syntax/ast/node.h>
#include <fp/syntax/ast/detail/base_node.h>

namespace fp::syntax::ast {

/**
 * Represents a syntax error that is caused when encountering a token that is
 * not a valid infix (or postfix) operator.
 */
struct infix_error : detail::base_node<infix_error> {
    /// The AST node which was supposed to be the infix operator's "LHS".
    ast::node lhs;

    /// The invalid infix token.
    const lex::tokenized_token& invalid_infix_token;

    infix_error(ast::node lhs, lex::token_iterator invalid_infix_token) :
        base_node(lhs.tokens().begin(), invalid_infix_token + 1),
        lhs(std::move(lhs)),
        invalid_infix_token(*invalid_infix_token)
    {}
};

} // namespace fp::syntax::ast
