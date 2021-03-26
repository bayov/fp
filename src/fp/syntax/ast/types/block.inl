#pragma once

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
struct block : public detail::base_sequence<block> {
    lex::token_iterator opening_brace;
    lex::token_iterator closing_brace;

    block(
        lex::token_iterator opening_brace,
        lex::token_iterator closing_brace,
        std::vector<node> nodes,
        std::vector<lex::token_iterator> separators
    ) :
        base_sequence(
            opening_brace,
            closing_brace + 1,
            std::move(nodes),
            std::move(separators)
        )
    {}
};

} // namespace fp::syntax::ast
