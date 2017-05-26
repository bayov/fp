#pragma once

#include <cstdint>

#include <fp/util/enum_class.h>
#include <fp/lex/keywords.h>

namespace fp::lex {

#define FP_TOKEN_ENUMERATOR(enumerator, _) enumerator

/// The actual type used to represent a @ref token.
using token_type = uint8_t;

/// Enumeration of all tokens in the language.
ENUM_CLASS(token, token_type,
    HEAD,           ///< Dummy token, placed at the front of a @see token_list.

    QUOTE,          ///< "
    COMMA,          ///< ,
    ANNOTATION,     ///< :
    SEMICOLON,      ///< ;
    OPTIONAL,       ///< ?
    DECORATOR,      ///< @
    BIT_NOT,        ///< ~
    MEMBER_ACCESS,  ///< .
    RANGE,          ///< ..
    CLOSED_RANGE,   ///< ...

    // brackets
    L_PAREN,        ///< (
    R_PAREN,        ///< )
    L_BRACKET,      ///< [
    R_BRACKET,      ///< ]
    L_BRACE,        ///< {
    R_BRACE,        ///< }

    // keywords
    FP_KEYWORDS_ENUM(FP_TOKEN_ENUMERATOR),

    // arrows
    TYPE_ARROW,     ///< ->
    LAMBDA_ARROW,   ///< =>

    // arithmetic
    PLUS,           ///< +
    MINUS,          ///< -
    MUL,            ///< *
    DIV,            ///< /
    MOD,            ///< %
    POW,            ///< **
    BIT_AND,        ///< &
    BIT_OR,         ///< |
    XOR,            ///< ^
    LSHIFT,         ///< <<
    RSHIFT,         ///< >>

    // assignments
    ASSIGN,         ///< =
    PLUS_ASSIGN,    ///< +=
    MINUS_ASSIGN,   ///< -=
    MUL_ASSIGN,     ///< *=
    DIV_ASSIGN,     ///< /=
    MOD_ASSIGN,     ///< %=
    POW_ASSIGN,     ///< **=
    BIT_AND_ASSIGN, ///< &=
    BIT_OR_ASSIGN,  ///< |=
    XOR_ASSIGN,     ///< ^=
    LSHIFT_ASSIGN,  ///< <<=
    RSHIFT_ASSIGN,  ///< >>=

    // comparisons
    EQ,             ///< ==
    NE,             ///< !=
    LT,             ///< <
    GT,             ///< >
    LTE,            ///< <=
    GTE,            ///< >=

    // increment & decrement
    INC,            ///< ++
    DEC,            ///< --

    // containing attributes
    COMMENT,        ///< # some comment...
    IDENTIFIER,     ///< some_identifier, Can_Be_CAPITALIZED
    INTEGER,        ///< 42, 0xFF, 0b11, 1`000`000, ...
    FLOAT,          ///< 3.14, 1.23e-10, ...
    CHAR,           ///< 'a'

    /**
     * String tokens are handled a bit differently.
     *
     * The lexer will tokenize `"Hello, World\n"` as `QUOTE STRING QUOTE`. But,
     * as we need to support string-interpolation (embedded expressions inside
     * strings), the following:
     *      "one plus one is {1 + 1}."
     *
     * will be tokenized as:
     *      QUOTE STRING L_BRACE INTEGER PLUS INTEGER R_BRACE STRING QUOTE
     *            ^~~~~~                                      ^~~~~~
     *            "one plus one is "                          "."
     */
    STRING,

    ERROR           ///< Error token
);

} // namespace fp::lex
