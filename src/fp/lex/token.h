#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>
#include <unordered_map>

namespace fp::lex {

/// Enumeration of all tokens in the language.
enum class token : uint8_t {
    ERROR,          ///< Error token, representing a lexical analysis error.

    QUOTE,          ///< "
    COMMA,          ///< ,
    ANNOTATION,     ///< :
    SCOPE,          ///< ::
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
    AND,
    AS,
    BREAK,
    CASE,
    CATCH,
    CLASS,
    CONCEPT,
    CONTINUE,
    DEFAULT,
    DO,
    ELSE,
    ENUM,
    EXPORT,
    FOR,
    IF,
    IMPLICIT,
    IMPORT,
    IN,
    MUT,
    NOT,
    OF,
    OR,
    RETURN,
    SWITCH,
    THROW,
    TRY,
    WHILE,

    // arrows
    TYPE_ARROW,     ///< ->
    LAMBDA_ARROW,   ///< =>

    // arithmetic
    PLUS,           ///< +
    MINUS,          ///< -
    MUL,            ///< *
    DIV,            ///< /
    MOD,            ///< %
    POW,            ///< ^
    BIT_AND,        ///< &
    BIT_OR,         ///< |
    XOR,            ///< TBD: Maybe a keyword `xor`? But then we have `xor=`
    SHL,            ///< <<
    SHR,            ///< >>

    // assignments
    ASSIGN,         ///< =
    PLUS_ASSIGN,    ///< +=
    MINUS_ASSIGN,   ///< -=
    MUL_ASSIGN,     ///< *=
    DIV_ASSIGN,     ///< /=
    MOD_ASSIGN,     ///< %=
    POW_ASSIGN,     ///< ^=
    BIT_AND_ASSIGN, ///< &=
    BIT_OR_ASSIGN,  ///< |=
    XOR_ASSIGN,     ///< TBD...
    SHL_ASSIGN,     ///< <<=
    SHR_ASSIGN,     ///< >>=

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
    NUMBER,         ///< 42, 0xFF, 0b11, 1'000'000, 3.14, 1.23e-10, ...
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
     *      QUOTE STRING L_BRACE NUMBER PLUS NUMBER R_BRACE STRING QUOTE
     *            ^~~~~~                                    ^~~~~~
     *            "one plus one is "                        "."
     */
    STRING
};

/// A mapping too all keyword tokens from their string representation.
extern std::unordered_map<std::string_view, token> keywords_map;

/**
 * Returns a string representation for a lex::token.
 *
 * E.g., for token::PLUS, "PLUS" will be returned.
 */
std::string_view token_name(token);

/// Prints a lex::token using lex::token_name.
std::ostream& operator<<(std::ostream&, token);

} // namespace fp::lex
