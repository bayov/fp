#pragma once

#include <fp/lex/token.h>
#include <fp/lex/detail/tokenization_state.h>

namespace fp::lex::detail {

/**
 * Tokenizes the binary op of `TOKEN`, or the assignment version of it
 * `TOKEN_ASSIGN`.
 */
template <token TOKEN, token TOKEN_ASSIGN>
void tokenize_binary_op(tokenization_state& s) {
    ++s.next;
    if (s.next_is('=')) {
        s.consume_and_push(TOKEN_ASSIGN);
    } else {
        s.push(TOKEN);
    }
}

/// Tokenizes one of `+`, `++`, or `+=`.
void tokenize_plus(tokenization_state& s) {
    if (s.next_is("++")) {
        ++s.next;
        s.consume_and_push(token::INC);
    } else {
        tokenize_binary_op<token::ADD, token::ADD_ASSIGN>(s);
    }
}

/// Tokenizes one of `-`, `--`, `->`, or `-=`.
void tokenize_minus_or_type_arrow(tokenization_state& s) {
    if (s.next_is("--")) {
        ++s.next;
        s.consume_and_push(token::DEC);
    } else if (s.next_is("->")) {
        ++s.next;
        s.consume_and_push(token::TYPE_ARROW);
    } else {
        tokenize_binary_op<token::SUB, token::SUB_ASSIGN>(s);
    }
}

/// Tokenizes one of `<`, `<=`, `<<`, or `<<=`.
void tokenize_lt_or_shl(tokenization_state& s) {
    if (s.next_is("<<")) {
        ++s.next;
        tokenize_binary_op<token::SHL, token::SHL_ASSIGN>(s);
    } else {
        tokenize_binary_op<token::LT, token::LTE>(s);
    }
}

/// Tokenizes one of `>`, `>=`, `>>`, or `>>=`.
void tokenize_gt_or_shr(tokenization_state& s) {
    if (s.next_is(">>")) {
        ++s.next;
        tokenize_binary_op<token::SHR, token::SHR_ASSIGN>(s);
    } else {
        tokenize_binary_op<token::GT, token::GTE>(s);
    }
}

/// Tokenizes one of `=`, `=>`, or `==`.
void tokenize_eq_or_lambda_arrow(tokenization_state& s) {
    if (s.next_is("=>")) {
        ++s.next;
        s.consume_and_push(token::LAMBDA_ARROW);
    } else {
        tokenize_binary_op<token::ASSIGN, token::EQ>(s);
    }
}

/// Tokenizes `!=`.
void tokenize_not_eq(tokenization_state& s) {
    ++s.next;
    if (s.next_is('=')) {
        s.consume_and_push(token::NE);
    } else {
        s.report_error("invalid character. Did you mean `not` or `!=`?")
            .add_primary(s.current_token_location());;
        s.push_dummy(token::ERROR);
    }
}

} // namespace fp::lex::detail
