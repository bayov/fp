#pragma once

#include <fp/util/constexpr_table.h>
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
    size_t operator()(symbol_t s) {
        return *reinterpret_cast<unsigned char*>(&s);
    }
};

void tokenize_error(tokenizer_state& s) { s.error(); }
inline void skip(tokenizer_state& s) { ++s.it; }
inline void line_feed(tokenizer_state& s) { s.newline(); }

inline void carriage_return(tokenizer_state& s) {
    if (s.next_is<'\n'>()) { ++s.it; } // CRLF (\r\n)
    s.newline();
}

template <token TOKEN>
void as(tokenizer_state& s) { s.tokenize_as<TOKEN>(); }

using tokenizers_table =
    util::constexpr_table<symbol_t, tokenizer_t, 256, symbol_to_index>
    ::set_default<tokenize_error>

    // whitespace
    ::set<'\t', skip>               // (0x09) horizontal tab
    ::set<'\n', line_feed>          // (0x0a) line feed
    ::set<'\v', skip>               // (0x0b) vertical tab
    ::set<'\f', skip>               // (0x0c) form feed
    ::set<'\r', carriage_return>    // (0x0d) horizontal tab
    ::set<' ' , skip>

    // string
    ::set<'\'', tokenize_char>
    ::set<'"' , tokenize_quote>
    ::set<'{' , tokenize_left_brace>
    ::set<'}' , tokenize_right_brace>

    // number
    ::set<'0' , tokenize_number>
    ::set<'1' , tokenize_number>
    ::set<'2' , tokenize_number>
    ::set<'3' , tokenize_number>
    ::set<'4' , tokenize_number>
    ::set<'5' , tokenize_number>
    ::set<'6' , tokenize_number>
    ::set<'7' , tokenize_number>
    ::set<'8' , tokenize_number>
    ::set<'9' , tokenize_number>
        
    // identifiers and keywords
    ::set<'A' , tokenize_identifier>
    ::set<'B' , tokenize_identifier>
    ::set<'C' , tokenize_identifier>
    ::set<'D' , tokenize_identifier>
    ::set<'E' , tokenize_identifier>
    ::set<'F' , tokenize_identifier>
    ::set<'G' , tokenize_identifier>
    ::set<'H' , tokenize_identifier>
    ::set<'I' , tokenize_identifier>
    ::set<'J' , tokenize_identifier>
    ::set<'K' , tokenize_identifier>
    ::set<'L' , tokenize_identifier>
    ::set<'M' , tokenize_identifier>
    ::set<'N' , tokenize_identifier>
    ::set<'O' , tokenize_identifier>
    ::set<'P' , tokenize_identifier>
    ::set<'Q' , tokenize_identifier>
    ::set<'R' , tokenize_identifier>
    ::set<'S' , tokenize_identifier>
    ::set<'T' , tokenize_identifier>
    ::set<'U' , tokenize_identifier>
    ::set<'V' , tokenize_identifier>
    ::set<'W' , tokenize_identifier>
    ::set<'X' , tokenize_identifier>
    ::set<'Y' , tokenize_identifier>
    ::set<'Z' , tokenize_identifier>
    ::set<'_' , tokenize_identifier>
    ::set<'a' , tokenize_keyword_or_identifier>
    ::set<'b' , tokenize_keyword_or_identifier>
    ::set<'c' , tokenize_keyword_or_identifier>
    ::set<'d' , tokenize_keyword_or_identifier>
    ::set<'e' , tokenize_keyword_or_identifier>
    ::set<'f' , tokenize_keyword_or_identifier>
    ::set<'g' , tokenize_keyword_or_identifier>
    ::set<'h' , tokenize_keyword_or_identifier>
    ::set<'i' , tokenize_keyword_or_identifier>
    ::set<'j' , tokenize_keyword_or_identifier>
    ::set<'k' , tokenize_keyword_or_identifier>
    ::set<'l' , tokenize_keyword_or_identifier>
    ::set<'m' , tokenize_keyword_or_identifier>
    ::set<'n' , tokenize_keyword_or_identifier>
    ::set<'o' , tokenize_keyword_or_identifier>
    ::set<'p' , tokenize_keyword_or_identifier>
    ::set<'q' , tokenize_keyword_or_identifier>
    ::set<'r' , tokenize_keyword_or_identifier>
    ::set<'s' , tokenize_keyword_or_identifier>
    ::set<'t' , tokenize_keyword_or_identifier>
    ::set<'u' , tokenize_keyword_or_identifier>
    ::set<'v' , tokenize_keyword_or_identifier>
    ::set<'w' , tokenize_keyword_or_identifier>
    ::set<'x' , tokenize_keyword_or_identifier>
    ::set<'y' , tokenize_keyword_or_identifier>
    ::set<'z' , tokenize_keyword_or_identifier>

    // binary-operators
    ::set<'+' , tokenize_plus_or_minus<'+'>>
    ::set<'-' , tokenize_plus_or_minus<'-'>>
    ::set<'*' , TOKENIZE_BINARY_OPS(MUL, '*', POW)>
    ::set<'/' , TOKENIZE_BINARY_OP(DIV)>
    ::set<'%' , TOKENIZE_BINARY_OP(MOD)>
    ::set<'&' , TOKENIZE_BINARY_OP(BIT_AND)>
    ::set<'|' , TOKENIZE_BINARY_OP(BIT_OR)>
    ::set<'^' , TOKENIZE_BINARY_OP(XOR)>
    ::set<'<' , TOKENIZE_COMPARISON_OR_BITSHIFT(LT, '<', LSHIFT)>
    ::set<'>' , TOKENIZE_COMPARISON_OR_BITSHIFT(GT, '>', RSHIFT)>
    ::set<'=' , tokenize_eq>

    // as-is
    ::set<'(' , as<token::L_PAREN>>
    ::set<')' , as<token::R_PAREN>>
    ::set<'[' , as<token::L_BRACKET>>
    ::set<']' , as<token::R_BRACKET>>
    ::set<',' , as<token::COMMA>>
    ::set<':' , as<token::ANNOTATION>>
    ::set<';' , as<token::SEMICOLON>>
    ::set<'?' , as<token::OPTIONAL>>
    ::set<'@' , as<token::DECORATOR>>
    ::set<'~' , as<token::BIT_NOT>>

    // misc
    ::set<'!' , tokenize_exclamation>
    ::set<'#' , tokenize_comment>
    ::set<'.' , tokenize_period>
;

} // fp::lex::detail
