#pragma once

#include "tokenizer_state.h"

namespace fp::lex::detail {

/**
 * Tokenize the following symbols as a string token (token::STRING), until
 * reaching either a `"` or an `{` terminator.
 *
 * @note
 *      If the string is empty, no token will be pushed to the token-list.
 */
inline void tokenize_string(tokenizer_state& s) {
    std::string value;
    for (;; ++s.it) {
        if (s.it == s.end || *s.it == '\n' || *s.it == '\r') {
            s.error(s.it, s.it, "Missing terminating `\"`");
        }
        if (*s.it == '"' || *s.it == '{') { break; }
        if (*s.it == '\\') {
            ++s.it;
            if (s.it == s.end) {
                s.error(s.it - 1, s.it, "Invalid escape sequence");
            }
            switch (*s.it) {
                case '"':
                    value += '"';
                    break;
                case '\\':
                    value += '\\';
                    break;
                case 'n':
                    value += '\n';
                    break;
                case 'r':
                    value += '\r';
                    break;
                case 't':
                    value += '\t';
                    break;
                case '0':
                    value += '\0';
                    break;
                default:
                    s.error(s.it - 1, s.it + 1, "Invalid escape sequence");
            }
        } else {
            value += *s.it;
        }
    }
    if (!value.empty()) { s.push<token::STRING>(std::move(value)); }
}

} // fp::lex::detail
