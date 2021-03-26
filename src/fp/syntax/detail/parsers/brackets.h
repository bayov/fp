#pragma once

#include <fp/syntax/detail/precedence.h>
#include <fp/syntax/detail/parsing_state.h>
#include <fp/syntax/detail/parsers/sequence.h>

namespace fp::syntax::detail {

ast::node parse_block(
    parsing_state& s,
    lex::token_iterator opening_brace,
    ast::node first_node
) {
    parsed_sequence r = parse_sequence(s, std::move(first_node));
    if (s.next == s.end) {
        s.report_error("unterminated opening brace {")
            .add_primary(
                opening_brace->source_location,
                "missing closing }"
            );
    }
    lex::token_iterator closing_brace = s.next++;
    return ast::block(
        opening_brace,
        closing_brace,
        std::move(r.nodes),
        std::move(r.separators)
    );
}

/// TODO: Document
ast::node parse_brackets(parsing_state& s) {
    lex::token_iterator opening_brace = s.next++;
    ast::node node = s.parse(precedence_table[lex::token::SEMICOLON]);
    if (s.next == s.end) {
        s.report_error("unterminated opening brace {")
            .add_primary(opening_brace->source_location, "missing closing }");
        return node;
    }
    switch (s.next->token) {
        case lex::token::SEMICOLON:
            return parse_block(s, opening_brace, std::move(node));
        default:
            s.report_error("unexpected token")
                .add_primary(s.next->source_location, "unexpected");
            return node;
    }
}

} // namespace fp::syntax::detail
