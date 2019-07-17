#pragma once

#include <optional>

#include <fp/lex/detail/tokenization_state.h>

namespace fp::lex::detail {

/**
 * Returns the current character's value.
 *
 * Also parses escape sequences (`\` followed by `n`, `0`, etc.).
 *
 * On error (invalid escape sequence), a std::nullopt will be returned.
 *
 * @param QUOTE
 *     When tokenizing a character literal, this should be a single-quote, and
 *     when tokenizing a string literal, this should be a double-quote. This
 *     just adds the `quote` character as a valid escape sequence.
 *
 * @todo Handle unicode characters.
 */
template <char_t QUOTE>
std::optional<char_t> unescaped_char(tokenization_state& s) {
    if (*s.next != '\\') { return *s.next; }
    source_iterator escape_begin = s.next;
    ++s.next; // skip backslash
    if (s.next == s.end) {
        s.report_error(escape_begin, s.end, "invalid escape sequence");
        return std::nullopt;
    }
    char_t c = *s.next;
    ++s.next; // skip over entire escape sequence
    switch (c) {
        case QUOTE: return QUOTE;
        case '\\':  return '\\';
        case 'n':   return '\n';
        case 'r':   return '\r';
        case 't':   return '\t';
        case '0':   return '\0';
        default:
            s.report_error(escape_begin, s.next, "invalid escape sequence");
    }
    return std::nullopt;
}

/**
 * Reports a diagnostic::error for a missing terminating character or string
 * literal quote.
 *
 * @tparam QUOTE
 *      The type of quote missing (either `'` or `"`").
 *
 * @param opening_quote_it
 *      Source code iterator to the opening quote character.
 */
template <char QUOTE>
inline void report_missing_termination_quote(
    tokenization_state& s,
    source_iterator opening_quote_it
) {
    std::string text =
        QUOTE == '\'' ?
        "missing terminating ' character" :
        "missing terminating \" character";
    s.report_error(opening_quote_it, opening_quote_it + 1, std::move(text));
}

/**
 * As part of error recovery, we produce a token::CHAR during tokenization of a
 * character literal even when encountering an error. This will serve as a dummy
 * attribute for token::CHAR in such cases.
 */
constexpr char_t DUMMY_CHAR = '#';

/// Tokenizes a single character (token::CHAR).
inline void tokenize_char(tokenization_state& s) {
    source_iterator opening_quote = s.next;
    ++s.next; // skip over opening `'`
    if (s.next == s.end || *s.next == '\n' || *s.next == '\r') {
        report_missing_termination_quote<'\''>(s, opening_quote);
        s.push<token::CHAR>(DUMMY_CHAR);
        s.push<token::ERROR>();
        return;
    }
    std::optional<char_t> value = unescaped_char<'\''>(s);
    if (!value) {
        // invalid escape sequence (error was already reported)
        s.push<token::CHAR>(DUMMY_CHAR);
        s.push<token::ERROR>();
        return;
    }
    if (!s.next_is<'\''>()) {
        report_missing_termination_quote<'\''>(s, opening_quote);
        s.push<token::CHAR>(DUMMY_CHAR);
        s.push<token::ERROR>();
        return;
    }
    ++s.next; // skip over closing `'`
    s.push<token::CHAR>(*value);
}

} // namespace fp::lex::detail
