#pragma once

#include <vector>

#include <fp/util/assert.h>
#include <fp/syntax/ast/detail/base_node.h>
#include <fp/syntax/ast/node.h>

namespace fp::syntax::ast::detail {

/**
 * A list of AST nodes, each separated with the same separator token.
 *
 * There are two available sequence types:
 *  - comma-sequence, where each node is separated by token::COMMA.
 *  - semicolon-sequence, where each node is separated by token::SEMICOLON.
 */
template <class Derived>
struct base_sequence : public detail::base_node<Derived> {
    /// The `ast::node`s that make up the sequence.
    std::vector<node> nodes;

    /**
     * The separator tokens that appear between the sequence's `nodes`.
     *
     * `separators[i]` is the `i`-th separating token, which appears right after
     * the `i`-th node (`nodes[i]`).
     *
     * The following always holds:
     * ~~~{.cpp}
     * separators.size() == nodes.size() - 1
     * ~~~
     */
    std::vector<lex::token_iterator> separators;

    base_sequence(
        lex::token_iterator from,
        lex::token_iterator to,
        std::vector<node> nodes,
        std::vector<lex::token_iterator> separators
    ) :
        detail::base_node<Derived>(from, to),
        nodes(std::move(nodes)),
        separators(std::move(separators))
    {
        FP_ASSERT(
            !separators.empty(),
            "a sequence must contain at least 1 separator token"
        );
        FP_ASSERT(
            separators.size() == nodes.size() - 1 ||
            separators.size() == nodes.size(),
            "there should be a separator between each node, and possibly one "
            "more after the last node (received " << nodes.size() << " nodes "
            "and " << separators.size() << " separators)"
        );
    }

    lex::token separator_token() const {
        return separators.front()->token;
    }
};

} // namespace fp::syntax::ast::detail
