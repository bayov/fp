#pragma once

#include <fp/util/table.h>
#include <fp/lex/detail/tokenization_state.h>
#include <fp/lex/detail/tokenizers/character_and_string.h>
#include <fp/lex/detail/tokenizers/number.h>
#include <fp/lex/detail/tokenizers/stray_character.h>
#include <fp/lex/detail/tokenizers/keyword_or_identifier.h>
#include <fp/lex/detail/tokenizers/whitespace.h>

namespace fp::lex::detail {

/**
 * A "tokenizer" is a function that consumes a specific character that appears
 * next in the source code (and possibly more) in order to create new tokens.
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
    t['\''] = tokenize_character;
    t['"' ] = tokenize_double_quote;
    t['{' ] = tokenize_left_brace;
    t['}' ] = tokenize_right_brace;

    // number
    t['0' ] = tokenize_number_with_zero_prefix;
    t['1' ] = tokenize_number_with_no_zero_prefix;
    t['2' ] = tokenize_number_with_no_zero_prefix;
    t['3' ] = tokenize_number_with_no_zero_prefix;
    t['4' ] = tokenize_number_with_no_zero_prefix;
    t['5' ] = tokenize_number_with_no_zero_prefix;
    t['6' ] = tokenize_number_with_no_zero_prefix;
    t['7' ] = tokenize_number_with_no_zero_prefix;
    t['8' ] = tokenize_number_with_no_zero_prefix;
    t['9' ] = tokenize_number_with_no_zero_prefix;

//    // identifiers and keywords
    t['A' ] = tokenize_keyword_or_identifier;
    t['B' ] = tokenize_keyword_or_identifier;
    t['C' ] = tokenize_keyword_or_identifier;
    t['D' ] = tokenize_keyword_or_identifier;
    t['E' ] = tokenize_keyword_or_identifier;
    t['F' ] = tokenize_keyword_or_identifier;
    t['G' ] = tokenize_keyword_or_identifier;
    t['H' ] = tokenize_keyword_or_identifier;
    t['I' ] = tokenize_keyword_or_identifier;
    t['J' ] = tokenize_keyword_or_identifier;
    t['K' ] = tokenize_keyword_or_identifier;
    t['L' ] = tokenize_keyword_or_identifier;
    t['M' ] = tokenize_keyword_or_identifier;
    t['N' ] = tokenize_keyword_or_identifier;
    t['O' ] = tokenize_keyword_or_identifier;
    t['P' ] = tokenize_keyword_or_identifier;
    t['Q' ] = tokenize_keyword_or_identifier;
    t['R' ] = tokenize_keyword_or_identifier;
    t['S' ] = tokenize_keyword_or_identifier;
    t['T' ] = tokenize_keyword_or_identifier;
    t['U' ] = tokenize_keyword_or_identifier;
    t['V' ] = tokenize_keyword_or_identifier;
    t['W' ] = tokenize_keyword_or_identifier;
    t['X' ] = tokenize_keyword_or_identifier;
    t['Y' ] = tokenize_keyword_or_identifier;
    t['Z' ] = tokenize_keyword_or_identifier;
    t['_' ] = tokenize_keyword_or_identifier;
    t['a' ] = tokenize_keyword_or_identifier;
    t['b' ] = tokenize_keyword_or_identifier;
    t['c' ] = tokenize_keyword_or_identifier;
    t['d' ] = tokenize_keyword_or_identifier;
    t['e' ] = tokenize_keyword_or_identifier;
    t['f' ] = tokenize_keyword_or_identifier;
    t['g' ] = tokenize_keyword_or_identifier;
    t['h' ] = tokenize_keyword_or_identifier;
    t['i' ] = tokenize_keyword_or_identifier;
    t['j' ] = tokenize_keyword_or_identifier;
    t['k' ] = tokenize_keyword_or_identifier;
    t['l' ] = tokenize_keyword_or_identifier;
    t['m' ] = tokenize_keyword_or_identifier;
    t['n' ] = tokenize_keyword_or_identifier;
    t['o' ] = tokenize_keyword_or_identifier;
    t['p' ] = tokenize_keyword_or_identifier;
    t['q' ] = tokenize_keyword_or_identifier;
    t['r' ] = tokenize_keyword_or_identifier;
    t['s' ] = tokenize_keyword_or_identifier;
    t['t' ] = tokenize_keyword_or_identifier;
    t['u' ] = tokenize_keyword_or_identifier;
    t['v' ] = tokenize_keyword_or_identifier;
    t['w' ] = tokenize_keyword_or_identifier;
    t['x' ] = tokenize_keyword_or_identifier;
    t['y' ] = tokenize_keyword_or_identifier;
    t['z' ] = tokenize_keyword_or_identifier;
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
