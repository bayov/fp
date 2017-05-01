#pragma once

#include <fp/lex/detail/tokenizer_state.h>

namespace fp::lex::detail {

/**
 * Tokenize the current symbol as `TOKEN`, or as the assignment version of it,
 * `TOKEN_ASSIGN`.
 */
template <token TOKEN, token TOKEN_ASSIGN>
void tokenize_binary_op(tokenizer_state& s) {
    if (s.next_is<'='>()) {
        s.it += 2;
        s.push<TOKEN_ASSIGN>();
    } else {
        ++s.it;
        s.push<TOKEN>();
    }
}

#define TOKENIZE_BINARY_OP(TOKEN)\
    tokenize_binary_op<token::TOKEN, token::TOKEN##_ASSIGN>

/**
 * Like @ref tokenize_binary_op, but for tokens which may have the same initial
 * symbol. E.g., for `*` (token::MUL), we expect one of the following:
 *
 *      - `*` to compose a token::MUL           (as `TOKEN`)
 *      - `*=` to compose a token::MUL_ASSIGN   (as `TOKEN_ASSIGN`)
 *      - `**` to compose a token::POW          (as `SECOND_TOKEN`)
 *      - `**=` to compose a token::POW_ASSIGN  (as `SECOND_TOKEN_ASSIGN`)
 *
 * @tparam SYMBOL
 *      The following symbol that will result in the second token.
 */
template <
    token TOKEN,
    token TOKEN_ASSIGN,
    symbol_t SYMBOL,
    token SECOND_TOKEN,
    token SECOND_TOKEN_ASSIGN
>
void token_binary_ops(tokenizer_state& s) {
    if (s.next_is<'='>()) {
        ++s.it;
        s.tokenize_as<TOKEN_ASSIGN>();
    } else if (s.next_is<SYMBOL>()) {
        ++s.it;
        tokenize_binary_op<SECOND_TOKEN, SECOND_TOKEN_ASSIGN>(s);
    } else {
        s.tokenize_as<TOKEN>();
    }
}

#define TOKENIZE_BINARY_OPS(TOKEN, SYMBOL, SECOND_TOKEN)\
    token_binary_ops<\
        token::TOKEN,\
        token::TOKEN##_ASSIGN,\
        SYMBOL,\
        token::SECOND_TOKEN,\
        token::SECOND_TOKEN##_ASSIGN\
    >

#define TOKENIZE_COMPARISON_OR_BITSHIFT(TOKEN, SYMBOL, SECOND_TOKEN)\
    token_binary_ops<\
        token::TOKEN,\
        token::TOKEN##E,\
        SYMBOL,\
        token::SECOND_TOKEN,\
        token::SECOND_TOKEN##_ASSIGN\
    >

/// Tokenize one of `+`, `-`, `++`, `--`, `+=`, or `-=`.
template <symbol_t PLUS_OR_MINUS>
void tokenize_plus_or_minus(tokenizer_state& s) {
    constexpr token t = PLUS_OR_MINUS == '+' ? token::PLUS : token::MINUS;
    constexpr token tt = PLUS_OR_MINUS == '+' ? token::INC : token::DEC;
    constexpr token te = PLUS_OR_MINUS == '+' ?
                         token::PLUS_ASSIGN : token::MINUS_ASSIGN;
    if (s.next_is<PLUS_OR_MINUS>()) {
        ++s.it;
        s.tokenize_as<tt>(); // `++` or `--`
    } else {
        tokenize_binary_op<t, te>(s);
    }
}

/// Tokenize one of `=`, `=>`, or `==`.
inline void tokenize_eq(tokenizer_state& s) {
    if (s.next_is<'='>()) {
        ++s.it;
        s.tokenize_as<token::EQ>();
    } else if (s.next_is<'>'>()) {
        ++s.it;
        s.tokenize_as<token::LAMBDA_ARROW>();
    } else {
        s.tokenize_as<token::ASSIGN>();
    }
};

} // fp::lex::detail
