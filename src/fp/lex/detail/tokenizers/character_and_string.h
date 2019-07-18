#pragma once

#include <optional>

#include <fp/lex/detail/tokenization_state.h>

namespace fp::lex::detail {

/**
 * Returns the quoted content of a character or string literal.
 *
 * The terminator of a quoted section is any of the following:
 *
 *  - end of input (`end`)
 *  - new-lines (\n) and carriage-returns (\r)
 *  - unescaped terminator character: ' for characters and " or { for strings
 *
 * @param begin
 *      Iterator to one character after the opening quote.
 * @param end
 *      Iterator to the end of the source code.
 */
template <source_char QUOTE>
source_view quoted_content(source_iterator begin, source_iterator end) {
    constexpr auto is_terminator = [](source_char c) {
        return c == QUOTE || (QUOTE == '"' && c == '{');
    };
    source_iterator it = begin;
    for (; it != end; ++it) {
        if (*it == '\n' || *it == '\r' || is_terminator(*it)) { break; }
        if (*it == '\\' && (it + 1) != end && is_terminator(*(it + 1))) {
            // skip escaped terminators
            ++it;
        }
    }
    return make_source_view(begin, it);
}

/**
 * Consumes a single char from a character or string literal, which could
 * potentially be represented as an escape sequence, and returns its value.
 *
 * On error (invalid character), a std::nullopt will be returned instead.
 *
 * @tparam QUOTE
 *     When tokenizing a character literal, this should be a single-quote, and
 *     when tokenizing a string literal, this should be a double-quote. This
 *     just adds the `QUOTE` character as a valid escape sequence.
 *
 * @param content
 *      The contents available for consumption (see detail::quoted_content).
 * @param[out] it
 *      This iterator will be updated to the position after consumption.
 *
 * @todo Handle `\xFF` escape sequences.
 * @todo Handle unicode characters (and `\u` escape sequences).
 */
template <char_t QUOTE>
std::optional<char_t> consume_char(
    tokenization_state& s,
    source_view content,
    source_iterator& it
) {
    // consume the first char, regardless of whether it is a blackslash or not
    it = content.begin() + 1;

    // if it is not a backslash, just return it as is
    if (content.front() != '\\') { return content.front(); }

    // a backslash cannot appear alone
    if (content.size() == 1) {
        s.report_error(content, "invalid escape sequence");
        return std::nullopt;
    }

    // consume the character that appears after the backslash
    ++it;

    switch (content[1]) {
        case QUOTE: return QUOTE;
        case '\\':  return '\\';
        case 'n':   return '\n';
        case 'r':   return '\r';
        case 't':   return '\t';
        case '0':   return '\0';
        default:
            s.report_error(content.begin(), it, "invalid escape sequence");
            return std::nullopt;
    }
}

/**
 * Reports a diagnostic::error for a missing terminating quote.
 *
 * @tparam QUOTE
 *      The type of quote missing (either `'` or `"`").
 *
 * @param opening_quote
 *      Iterator to the opening quote character.
 */
template <char QUOTE>
inline void report_missing_terminating_quote(
    tokenization_state& s,
    source_iterator opening_quote
) {
    const char* text =
        QUOTE == '\'' ?
        "missing terminating ' character" :
        "missing terminating \" character";
    s.report_error(opening_quote, opening_quote + 1, text);
}

/// Tokenizes a single character (token::CHAR).
inline void tokenize_char(tokenization_state& s) {
    // skip over opening quote
    source_iterator opening_quote = s.next;
    ++s.next;

    // set the tokenization iterator to the end of the quoted content
    source_view quoted_content = detail::quoted_content<'\''>(s.next, s.end);
    s.next = quoted_content.end();

    // ensure that the quoted content ends with a terminating quote
    if (!s.next_is<'\''>()) {
        report_missing_terminating_quote<'\''>(s, opening_quote);
        s.push_dummy<token::CHAR>();
        s.push<token::ERROR>(); // for error recovery in later stages
        return;
    }

    // consume the terminating quote
    ++s.next;

    // a character literal cannot be empty!
    if (quoted_content.empty()) {
        s.report_error("empty character literal");
        s.push_dummy<token::CHAR>();
        return;
    }

    // consume a character from the quoted content
    source_iterator consume_end;
    std::optional<char_t> char_value =
        consume_char<'\''>(s, quoted_content, consume_end);

    if (!char_value) {
        // detail::consume_char already reported an error, so just push
        // token::CHAR with the dummy error value and return
        s.push_dummy<token::CHAR>();
        return;
    }

    // a character literal must contain exactly one character!
    if (consume_end != quoted_content.end()) {
        s.report_error("character literal contains more than one character");
        s.push_dummy<token::CHAR>();
        return;
    }

    s.push<token::CHAR>(*char_value);
}

/**
 * Tokenizes the next characters as token::STRING and then a terminating `"`
 * or `{` (token::QUOTE or token::L_BRACE).
 *
 * If the string is empty no token::STRING will be pushed (but a terminating
 * token::QUOTE or token::L_BRACE will be pushed regardless).
 */
inline void tokenize_string(tokenization_state& s) {
    // set the tokenization iterator to the end of the quoted content
    source_view quoted_content = detail::quoted_content<'"'>(s.next, s.end);
    s.next = quoted_content.end();

    // ensure that the quoted content ends with a terminating character
    if (!s.next_is<'"'>() && !s.next_is<'{'>()) {
        source_iterator opening_quote =
            s.string_interpolation_stack.current_frame().opening_quote;
        report_missing_terminating_quote<'"'>(s, opening_quote);
        if (!quoted_content.empty()) {
            s.push_dummy<token::STRING>();
        }
        s.push<token::ERROR>();
        return;
    }

    // parse the quoted content into the string token's `value`.
    token_attribute_t<token::STRING> value;
    value.reserve(quoted_content.size());
    while (!quoted_content.empty()) {
        // consume a character from the quoted content
        source_iterator consume_end;
        std::optional<char_t> char_value =
            consume_char<'"'>(s, quoted_content, consume_end);
        quoted_content = make_source_view(consume_end, quoted_content.end());

        if (!char_value) {
            // detail::consume_char already reported an error, so just push
            // token::STRING with the dummy error value and return
            s.push_dummy<token::STRING>();
            return;
        }

        if (*char_value > 127) {
            s.report_error("unicode string literals are not supported yet");
            s.push_dummy<token::STRING>();
        }

        value += char(*char_value);
    }

    s.push<token::STRING>(std::move(value));
}

} // namespace fp::lex::detail
