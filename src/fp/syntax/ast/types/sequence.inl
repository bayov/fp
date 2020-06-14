#pragma once

#include <vector>

#include <fp/syntax/ast/detail/base_node.h>
#include <fp/syntax/ast/node.h>

namespace fp::syntax::ast {

namespace detail {

/**
 * Given a `ast::sequence`'s nodes and separators, returns a view to the tokens
 * that would make up the sequence, regardless of whether it has a trailing-
 * separator or not.
 */
static lex::tokenized_view sequence_tokens(
    const std::vector<node>& nodes,
    const std::vector<lex::token_iterator>& separators
) {
    lex::token_iterator from = nodes.front().tokens().begin();
    lex::token_iterator to =
        separators.size() == nodes.size() ?
        separators.back() :
        nodes.back().tokens().end();
    return {from, to};
}

} // namespace detail

/**
 * A list of AST nodes, each separated with the same separator token.
 *
 * There are two available sequence types:
 *  - comma-sequence, where each node is separated by lex::token::COMMA.
 *  - semicolon-sequence, where each node is separated by lex::token::SEMICOLON.
 *
 * The number of `separators` is either equal to `nodes`, or 1 less than it,
 * depending on whether the last separator is a trailing comma (or trailing
 * semicolon).
 */
struct sequence : public detail::base_node<sequence> {
    /**
     * The separator token (appears between each two nodes in the sequence).
     *
     * This is either lex::token::COMMA or lex::token::SEMICOLON.
     */
    lex::token separator_token;

    /// The `ast::node`s that make up the sequence.
    std::vector<node> nodes;

    /**
     * The separator tokens that appear between the sequence's `nodes`.
     *
     * `separators[i]` is the `i`-th separating token, which appears right after
     * the `i`-th node (`nodes[i]`).
     *
     * When `sequence.has_trailing_separator()` is true, `separators.size()`
     * equals `nodes.size()`. Otherwise: `separators.size() == nodes.size() - 1`
     */
    std::vector<lex::token_iterator> separators;

    sequence(
        lex::token separator_token,
        std::vector<node> nodes,
        std::vector<lex::token_iterator> separators
    ) :
        base_node(detail::sequence_tokens(nodes, separators)),
        separator_token(separator_token),
        nodes(std::move(nodes)),
        separators(std::move(separators))
    {}

    /// Returns true if the last separator is a trailing one.
    bool has_trailing_separator() const {
        return separators.size() == nodes.size();
    }
};

} // namespace fp::syntax::ast
