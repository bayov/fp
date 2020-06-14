#pragma once

#include <fp/syntax/detail/parsing_state.h>

namespace fp::syntax::detail {

/**
 * Parses the next token as an ast::sequence.
 *
 * Assumes that the next token is a valid sequence-separator (i.e.
 * lex::token::COMMA or lex::token::SEMICOLON).
 */
ast::node parse_sequence(parsing_state& s, ast::node lhs) {
    std::vector<ast::node> nodes;
    std::vector<lex::token_iterator> separators;

    nodes.push_back(std::move(lhs));
    separators.push_back(s.next++);

    lex::token separator_token = separators.back()->token;
    precedence_t separator_precedence = precedence_table[separator_token];

    while (s.next != s.end) {
        // if the next token cannot be parsed as a prefix-token, we'll consider
        // the previous separator to be trailing, and finish the sequence
        if (prefix_parser_table[s.next->token] == parse_prefix_error) {
            break;
        }
        nodes.push_back(s.parse(separator_precedence));
        if (s.next_is(separator_token)) {
            separators.push_back(s.next++);
            continue;
        } else {
            break;
        }
    }
    return ast::sequence(
        separator_token,
        std::move(nodes),
        std::move(separators)
    );
}

} // namespace fp::syntax::detail
