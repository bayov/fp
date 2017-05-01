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
char unescaped_char(tokenizer_state& s) {
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

/// Tokenize a single character (token::CHAR).
inline void tokenize_char(tokenizer_state& s) {
    ++s.it; // skip over opening `'`
    if (s.it == s.end || *s.it == '\n' || *s.it == '\r') { s.error(); }
    auto value = unescaped_char<'\''>(s);
    ++s.it; // skip over character value
    if (s.it == s.end || *s.it != '\'') {
        auto d =  diagnostic::error(
            s.location(s.it, s.it),
            "Missing terminating `'`"
        );
        d.add_supplement(s.location());
    }
    ++s.it; // skip over closing `'`
    s.push<token::CHAR>(value);
}

/**
 * Tokenize the following symbols as a string token (token::STRING), and a
 * terminating `"` or `{` (token::QUOTE or token::L_BRACE).
 *
 * @note
 *      If the string is empty, no token::STRING will be pushed.
 */
inline void tokenize_string(tokenizer_state& s) {
    std::string value;
    while (*s.it != '"' && *s.it != '{') {
        if (s.it == s.end || *s.it == '\n' || *s.it == '\r') {
            s.error(s.it, s.it, "Missing terminating `\"`");
            // in order to recover from the error, we insert a terminator
            s.push<token::QUOTE>();
            return;
        }
        value += unescaped_char<'"'>(s);
        ++s.it;
    }
    if (!value.empty()) { s.push<token::STRING>(std::move(value)); }
    s.start_next_token();
    if (*s.it == '"') {
        s.tokenize_as<token::QUOTE>();
    } else { // *s.it == '{'
        s.string_iterpolation_stack.push_back(0);
        s.tokenize_as<token::L_BRACE>();
    }
}

/**
 * Tokenize a quote (token::QUOTE), a string section (token::STRING), and
 * a terminator (token::QUOTE or token::L_BRACE).
 */
inline void tokenize_quote(tokenizer_state& s) {
    s.tokenize_as<token::QUOTE>();
    s.start_next_token();
    tokenize_string(s);
}

/**
 * Tokenize a token::L_BRACE, which also increments the current number of open
 * braces on top of the string interpolation stack.
 */
inline void tokenize_left_brace(tokenizer_state& s) {
    s.tokenize_as<token::L_BRACE>();
    if (!s.string_iterpolation_stack.empty()) {
        ++s.string_iterpolation_stack.back();
    }
}

/**
 * Tokenize a token::R_BRACE, which also decrements the current number of open
 * braces on top of the string interpolation stack.
 *
 * If this number reaches 0, the top of the stack is popped, and a string
 * section (token::STRING) and a delimiter token::QUOTE or token::L_BRACE) will
 * be tokenized.
 */
inline void tokenize_right_brace(tokenizer_state& s) {
    s.tokenize_as<token::R_BRACE>();
    if (!s.string_iterpolation_stack.empty()) {
        if (s.string_iterpolation_stack.back() == 0) {
            s.string_iterpolation_stack.pop_back();
            s.start_next_token();
            tokenize_string(s);
        } else {
            --s.string_iterpolation_stack.back();
        }
    }
}

} // fp::lex::detail
