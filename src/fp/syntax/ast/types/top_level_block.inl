#pragma once

#include <fp/util/assert.h>
#include <fp/syntax/ast/detail/base_sequence.h>

namespace fp::syntax::ast {

/**
 * A top-level block is the same as ast::block, but its enclosing curly-braces
 * are implicit.
 *
 * The parser acts as if every piece of source-code is enclosed by imaginative
 * curly-braces. That is why semicolons, which are only allowed to appear as
 * separators in an ast::block, are also allowed in top-level source-code.
 */
struct top_level_block : public detail::base_sequence<top_level_block> {
    top_level_block(
        std::vector<node> nodes,
        std::vector<lex::token_iterator> separators
    ) :
        base_sequence(
            nodes.front().tokens().begin(),
            nodes.back().tokens().end(),
            std::move(nodes),
            std::move(separators)
        )
    {}
};

} // namespace fp::syntax::ast
