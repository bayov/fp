#pragma once

#include <fp/util/table.h>
#include <fp/lex/detail/tokenization_state.h>
#include <fp/lex/detail/tokenizers/stray_character.h>
#include <fp/lex/detail/tokenizers/string.h>
#include <fp/lex/detail/tokenizers/whitespace.h>

namespace fp::lex::detail {

/**
 * A "tokenizer" is a function that consumes a specific character that appears
 * next in the source code (and possibly more) in order to create a new token.
 *
 * Such functions are stored as part of a dispatch table of tokenizers from each
 * possible ASCII character: detail::tokenizers_table.
 */
using tokenizer_t = void (*)(tokenization_state&);

/**
 * Maps an ASCII character (-128...127) to an index (0...255) in the tokenizers
 * dispatch table: detail::tokenizers_table.
 */
struct source_char_to_index {
    constexpr size_t operator()(source_char c) const {
        return size_t((unsigned char)c);
    }
};
//
///// Like @ref line_feed, but skips over CRLF (`\r\n`) when encountered.
//inline void carriage_return(tokenizer_state& s) {
//    if (s.next_is<'\n'>()) { ++s.it; }
//    line_feed(s);
//}
//
///// Tokenize the symbol as `TOKEN`.
//template <token TOKEN>
//void as(tokenizer_state& s) { s.tokenize_as<TOKEN>(); }

using tokenizers_table_t = util::table<
    source_char,         // key
    tokenizer_t,         // value
    256,                 // number of entries
    source_char_to_index // maps key to table entry index
>;

/**
 * Tokenizers dispatch table.
 *
 * This table maps an ASCII character acting as the next character in the source
 * code to the tokenizer function (detail::tokenizer_t) that will be used to
 * handle it.
 */
constexpr auto tokenizers_table = tokenizers_table_t([](auto& t) {
    // Any ASCII character that is not handled by any of the tokenizers below
    // will be treated as a stray character in the source code.
    t.set_default(stray_character);

    // whitespace
    t['\t'] = ignore;          // (0x09) horizontal tab
    t['\n'] = line_feed;       // (0x0a) line feed
    t['\v'] = ignore;          // (0x0b) vertical tab
    t['\f'] = ignore;          // (0x0c) form feed
    t['\r'] = carriage_return; // (0x0d) horizontal tab
    t[' ' ] = ignore;          // (0x20) space

    // string
    t['\''] = tokenize_char;
//    t['"' ] = tokenizer::quote;
//    t['{' ] = tokenizer::left_brace;
//    t['}' ] = tokenizer::right_brace;

//    // number
//    t['0' ] = tokenizer::number;
//    t['1' ] = tokenizer::number;
//    t['2' ] = tokenizer::number;
//    t['3' ] = tokenizer::number;
//    t['4' ] = tokenizer::number;
//    t['5' ] = tokenizer::number;
//    t['6' ] = tokenizer::number;
//    t['7' ] = tokenizer::number;
//    t['8' ] = tokenizer::number;
//    t['9' ] = tokenizer::number;
//
//    // identifiers and keywords
//    t['A' ] = tokenizer::identifier;
//    t['B' ] = tokenizer::identifier;
//    t['C' ] = tokenizer::identifier;
//    t['D' ] = tokenizer::identifier;
//    t['E' ] = tokenizer::identifier;
//    t['F' ] = tokenizer::identifier;
//    t['G' ] = tokenizer::identifier;
//    t['H' ] = tokenizer::identifier;
//    t['I' ] = tokenizer::identifier;
//    t['J' ] = tokenizer::identifier;
//    t['K' ] = tokenizer::identifier;
//    t['L' ] = tokenizer::identifier;
//    t['M' ] = tokenizer::identifier;
//    t['N' ] = tokenizer::identifier;
//    t['O' ] = tokenizer::identifier;
//    t['P' ] = tokenizer::identifier;
//    t['Q' ] = tokenizer::identifier;
//    t['R' ] = tokenizer::identifier;
//    t['S' ] = tokenizer::identifier;
//    t['T' ] = tokenizer::identifier;
//    t['U' ] = tokenizer::identifier;
//    t['V' ] = tokenizer::identifier;
//    t['W' ] = tokenizer::identifier;
//    t['X' ] = tokenizer::identifier;
//    t['Y' ] = tokenizer::identifier;
//    t['Z' ] = tokenizer::identifier;
//    t['_' ] = tokenizer::identifier;
//    t['a' ] = tokenizer::keyword_or_identifier;
//    t['b' ] = tokenizer::keyword_or_identifier;
//    t['c' ] = tokenizer::keyword_or_identifier;
//    t['d' ] = tokenizer::keyword_or_identifier;
//    t['e' ] = tokenizer::keyword_or_identifier;
//    t['f' ] = tokenizer::keyword_or_identifier;
//    t['g' ] = tokenizer::keyword_or_identifier;
//    t['h' ] = tokenizer::keyword_or_identifier;
//    t['i' ] = tokenizer::keyword_or_identifier;
//    t['j' ] = tokenizer::keyword_or_identifier;
//    t['k' ] = tokenizer::keyword_or_identifier;
//    t['l' ] = tokenizer::keyword_or_identifier;
//    t['m' ] = tokenizer::keyword_or_identifier;
//    t['n' ] = tokenizer::keyword_or_identifier;
//    t['o' ] = tokenizer::keyword_or_identifier;
//    t['p' ] = tokenizer::keyword_or_identifier;
//    t['q' ] = tokenizer::keyword_or_identifier;
//    t['r' ] = tokenizer::keyword_or_identifier;
//    t['s' ] = tokenizer::keyword_or_identifier;
//    t['t' ] = tokenizer::keyword_or_identifier;
//    t['u' ] = tokenizer::keyword_or_identifier;
//    t['v' ] = tokenizer::keyword_or_identifier;
//    t['w' ] = tokenizer::keyword_or_identifier;
//    t['x' ] = tokenizer::keyword_or_identifier;
//    t['y' ] = tokenizer::keyword_or_identifier;
//    t['z' ] = tokenizer::keyword_or_identifier;
//
//    // binary-operators
//    t['+' ] = tokenizer::plus;
//    t['-' ] = tokenizer::minus;
//    t['*' ] = TOKENIZE_BINARY_OPS(MUL, '*', POW);
//    t['/' ] = TOKENIZE_BINARY_OP(DIV);
//    t['%' ] = TOKENIZE_BINARY_OP(MOD);
//    t['&' ] = TOKENIZE_BINARY_OP(BIT_AND);
//    t['|' ] = TOKENIZE_BINARY_OP(BIT_OR);
//    t['^' ] = TOKENIZE_BINARY_OP(XOR);
//    t['<' ] = TOKENIZE_COMPARISON_OR_BITSHIFT(LT, '<', LSHIFT);
//    t['>' ] = TOKENIZE_COMPARISON_OR_BITSHIFT(GT, '>', RSHIFT);
//    t['=' ] = tokenize_eq;
//
//    // as-is
//    t['(' ] = as<token::L_PAREN>;
//    t[')' ] = as<token::R_PAREN>;
//    t['[' ] = as<token::L_BRACKET>;
//    t[']' ] = as<token::R_BRACKET>;
//    t[',' ] = as<token::COMMA>;
//    t[';' ] = as<token::SEMICOLON>;
//    t['?' ] = as<token::OPTIONAL>;
//    t['@' ] = as<token::DECORATOR>;
//    t['~' ] = as<token::BIT_NOT>;
//
//    // misc
//    t[':' ] = tokenize_colon;
//    t['!' ] = tokenize_exclamation;
//    t['#' ] = tokenize_comment;
//    t['.' ] = tokenize_period;

    return t;
});

} // namespace fp::lex::detail
