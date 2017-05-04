#pragma once

#include <fp/util/table.h>
#include <fp/lex/detail/tokenizer_state.h>
#include <fp/lex/detail/tokenizers/tokenize_exclamation.h>
#include <fp/lex/detail/tokenizers/tokenize_string.h>
#include <fp/lex/detail/tokenizers/tokenize_comment.h>
#include <fp/lex/detail/tokenizers/tokenize_binary_op.h>
#include <fp/lex/detail/tokenizers/tokenize_period.h>
#include <fp/lex/detail/tokenizers/tokenize_number.h>
#include <fp/lex/detail/tokenizers/tokenize_keyword_or_identifier.h>

namespace fp::lex::detail {

/// A symbol handler function signature.
using tokenizer_t = void (*)(tokenizer_state&);

/// Maps a symbol (-128...127) to an index (0...255).
struct symbol_to_index {
    constexpr size_t operator()(symbol_t s) { return size_t((unsigned char)s); }
};

/// Tokenize the symbol as a token::ERROR, and report a diagnostic error.
void error(tokenizer_state& s) {
    s.tokenize_as<token::ERROR_IGNORE>();
    s.error();
}

void error_op(tokenizer_state& s) {
    s.tokenize_as<token::ERROR_OP>();
    s.error();
}

/// Skip over a symbol.
inline void skip(tokenizer_state& s) { ++s.it; }

/// Skip over a symbol and start a new line.
inline void line_feed(tokenizer_state& s) {
    ++s.it;
    s.newline();
}

/// Like @ref line_feed, but skips over CRLF (`\r\n`) when encountered.
inline void carriage_return(tokenizer_state& s) {
    if (s.next_is<'\n'>()) { ++s.it; }
    line_feed(s);
}

/// Tokenize the symbol as `TOKEN`.
template <token TOKEN>
void as(tokenizer_state& s) { s.tokenize_as<TOKEN>(); }

/// Tokenizer dispatch table (maps symbols to tokenizers).
constexpr auto tokenizers_table = ([]() {
    using table_t = util::table<symbol_t, tokenizer_t, 256, symbol_to_index>;
    auto t = table_t::with_default(error);

    // whitespace
    t['\t'] = skip;               // (0x09) horizontal tab
    t['\n'] = line_feed;          // (0x0a) line feed
    t['\v'] = skip;               // (0x0b) vertical tab
    t['\f'] = skip;               // (0x0c) form feed
    t['\r'] = carriage_return;    // (0x0d) horizontal tab
    t[' ' ] = skip;

    // string
    t['\''] = tokenize_char;
    t['"' ] = tokenize_quote;
    t['{' ] = tokenize_left_brace;
    t['}' ] = tokenize_right_brace;

    // number
    t['0' ] = tokenize_number;
    t['1' ] = tokenize_number;
    t['2' ] = tokenize_number;
    t['3' ] = tokenize_number;
    t['4' ] = tokenize_number;
    t['5' ] = tokenize_number;
    t['6' ] = tokenize_number;
    t['7' ] = tokenize_number;
    t['8' ] = tokenize_number;
    t['9' ] = tokenize_number;

    // identifiers and keywords
    t['A' ] = tokenize_identifier;
    t['B' ] = tokenize_identifier;
    t['C' ] = tokenize_identifier;
    t['D' ] = tokenize_identifier;
    t['E' ] = tokenize_identifier;
    t['F' ] = tokenize_identifier;
    t['G' ] = tokenize_identifier;
    t['H' ] = tokenize_identifier;
    t['I' ] = tokenize_identifier;
    t['J' ] = tokenize_identifier;
    t['K' ] = tokenize_identifier;
    t['L' ] = tokenize_identifier;
    t['M' ] = tokenize_identifier;
    t['N' ] = tokenize_identifier;
    t['O' ] = tokenize_identifier;
    t['P' ] = tokenize_identifier;
    t['Q' ] = tokenize_identifier;
    t['R' ] = tokenize_identifier;
    t['S' ] = tokenize_identifier;
    t['T' ] = tokenize_identifier;
    t['U' ] = tokenize_identifier;
    t['V' ] = tokenize_identifier;
    t['W' ] = tokenize_identifier;
    t['X' ] = tokenize_identifier;
    t['Y' ] = tokenize_identifier;
    t['Z' ] = tokenize_identifier;
    t['_' ] = tokenize_identifier;
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

    // binary-operators
    t['+' ] = tokenize_plus;
    t['-' ] = tokenize_minus;
    t['*' ] = TOKENIZE_BINARY_OPS(MUL, '*', POW);
    t['/' ] = TOKENIZE_BINARY_OP(DIV);
    t['%' ] = TOKENIZE_BINARY_OP(MOD);
    t['&' ] = TOKENIZE_BINARY_OP(BIT_AND);
    t['|' ] = TOKENIZE_BINARY_OP(BIT_OR);
    t['^' ] = TOKENIZE_BINARY_OP(XOR);
    t['<' ] = TOKENIZE_COMPARISON_OR_BITSHIFT(LT, '<', LSHIFT);
    t['>' ] = TOKENIZE_COMPARISON_OR_BITSHIFT(GT, '>', RSHIFT);
    t['=' ] = tokenize_eq;

    // as-is
    t['(' ] = as<token::L_PAREN>;
    t[')' ] = as<token::R_PAREN>;
    t['[' ] = as<token::L_BRACKET>;
    t[']' ] = as<token::R_BRACKET>;
    t[',' ] = as<token::COMMA>;
    t[':' ] = as<token::ANNOTATION>;
    t[';' ] = as<token::SEMICOLON>;
    t['?' ] = as<token::OPTIONAL>;
    t['@' ] = as<token::DECORATOR>;
    t['~' ] = as<token::BIT_NOT>;

    // misc
    t['!' ] = tokenize_exclamation;
    t['#' ] = tokenize_comment;
    t['.' ] = tokenize_period;

    // errors
    t['$' ] = error_op;
    t['\\'] = error_op;

    return t;
})();

} // namespace fp::lex::detail
