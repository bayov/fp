#pragma once

#include <fp/syntax/detail/precedence.h>
#include <fp/syntax/detail/parsing_state.h>

namespace fp::syntax::detail {

/// Parses the next token as ast::if_.
ast::node parse_if(parsing_state& s) {
    lex::token_iterator if_token = s.next++;
    ast::node condition = s.parse(0);
    if (condition.is<ast::empty>()) {
        s.report_error("missing `if` condition")
            .add_primary(
                if_token->source_location.slice_end(),
                "missing condition here"
            )
            .add_contextual(if_token->source_location);
    }
    // even when missing {, we'll parse the next node as the body of the
    // ast::if_ node, to try to recover from the error
    bool missing_opening_brace = !s.next_is(lex::token::L_BRACE);
    ast::node body = s.parse(0);
    if (missing_opening_brace) {
        fp::source_location missing_brace_location =
            condition.source_location().slice_end();
        s.report_error("missing { after `if` condition")
            .add_primary(missing_brace_location, "missing { here")
            .add_contextual(if_token->source_location)
            .add_contextual(condition.source_location())
            .add_contextual(body.source_location());
    }
    return ast::if_(if_token, std::move(condition), std::move(body));
}

} // namespace fp::syntax::detail
