#pragma once

#include <fp/lex/detail/tokenizer_state.h>

namespace fp::lex::detail {

/**
 * @return The current symbol as a character value.
 *
 * Also parses escape sequences (`\` followed by `n`, `0`, `\`, etc.). The given
 * `QUOTE` will also add `QUOTE` to the escape sequence list (which should be
 * `"` for strings and `'` for characters).
 */
template <char QUOTE>
inline char unescaped_char(tokenizer_state& s) {
    if (*s.it != '\\') { return *s.it; }
    ++s.it;
    if (s.it == s.end) { s.error(s.it - 1, s.it, "Invalid escape sequence"); }
    switch (*s.it) {
        case QUOTE: return QUOTE;
        case '\\':  return '\\';
        case 'n':   return '\n';
        case 'r':   return '\r';
        case 't':   return '\t';
        case '0':   return '\0';
        default:    s.error(s.it - 1, s.it + 1, "Invalid escape sequence");
    }
    return 0; // should not reach here
}

inline void tokenize_char(tokenizer_state& s) {
    ++s.it; // skip over opening `'`
    if (s.it == s.end || *s.it == '\n' || *s.it == '\r') { s.error(); }
    auto value = unescaped_char<'\''>(s);
    ++s.it; // skip over character value
    if (s.it == s.end || *s.it != '\'') {
        s.error(s.it, s.it, "Missing terminating `'`");
    }
    ++s.it; // skip over closing `'`
    s.push<token::CHAR>(value);
}

/**
 * Tokenize the following symbols as a string token (token::STRING), until
 * reaching either a `"` or an `{` terminator.
 *
 * @note
 *      If the string is empty, no token will be pushed to the token-list.
 */
inline void tokenize_string(tokenizer_state& s) {
    std::string value;
    while (*s.it != '"' && *s.it != '{') {
        if (s.it == s.end || *s.it == '\n' || *s.it == '\r') {
            s.error(s.it, s.it, "Missing terminating `\"`");
        }
        value += unescaped_char<'"'>(s);
        ++s.it;
    }
    if (!value.empty()) { s.push<token::STRING>(std::move(value)); }
}

} // fp::lex::detail
