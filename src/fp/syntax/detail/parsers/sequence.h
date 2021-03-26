#pragma once

#include <fp/syntax/detail/parsing_state.h>

namespace fp::syntax::detail {

struct parsed_sequence {
    std::vector<ast::node> nodes;
    std::vector<lex::token_iterator> separators;
};

/**
 * Parses the next token as an ast::sequence.
 *
 * Assumes that the next token is a valid sequence-separator (i.e.
 * token::COMMA or token::SEMICOLON).
 */
parsed_sequence parse_sequence(
    parsing_state& s,
    ast::node lhs
) {
    parsed_sequence result;
    result.nodes.push_back(std::move(lhs));
    result.separators.push_back(s.next++);

    lex::token separator_token = result.separators.front()->token;
    precedence_t separator_precedence = precedence_table[separator_token];

    while (s.next != s.end) {
        if (s.next_is(separator_token)) {
            result.separators.push_back(s.next++);
        } else {
            break;
        }
        result.nodes.push_back(s.parse(separator_precedence));
        if (s.next_is(separator_token)) {
            continue;
        } else {
            break;
        }
    }
    return result;
}

} // namespace fp::syntax::detail
