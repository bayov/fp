#include <optional>

#include "character_and_string.h"

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
template <char QUOTE>
source_view quoted_content(source_iterator begin, source_iterator end) {
    constexpr auto is_terminator = [](char c) {
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
    return {begin, it};
}

/**
 * Consumes a single char from a character or string literal, which could
 * potentially be represented as an escape sequence, and returns its value.
 *
 * The given content must be known to have a terminating character, since it
 * assumes that no backslash can appear as its last character.
 *
 * On error (invalid character), a std::nullopt will be returned instead.
 *
 * At the moment, Unicode is not supported. When encountering a UTF-8 byte, it
 * will the entire Unicode code point will be consumed (2 to 4 bytes), and
 * std::nullopt will be returned to denote an error.
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
    // skip the first char, regardless of whether it is a blackslash or not
    it = content.begin() + 1;

    // UTF-8 not supported yet
    if (content.front() & 0x80) {
        for (; it != content.end() && *it & 0x80; ++it) {}
        s.report_error("Unicode is not supported yet")
            .add_primary(
                s.location(content.begin(), it),
                "Unicode literals are not supported yet, sorry!"
            );
        return std::nullopt;
    }

    // if it is not a backslash, just return it as is
    if (content.front() != '\\') { return content.front(); }

    // skip the character that appears after the backslash
    ++it;

    // a left-brace escape sequence is only valid inside a string
    if (QUOTE == '"' && content[1] == '{') { return '{'; }

    switch (content[1]) {
        case QUOTE: return QUOTE;
        case '\\':  return '\\';
        case 'n':   return '\n';
        case 'r':   return '\r';
        case 't':   return '\t';
        case '0':   return '\0';
    }

    s.report_error("invalid escape sequence")
        .add_primary(
            s.location(content.begin(), it),
            "invalid escape sequence"
        );
    return std::nullopt;
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
void report_missing_terminating_quote(
    tokenization_state& s,
    source_iterator opening_quote
) {
    const char* text =
        QUOTE == '\'' ?
        "missing terminating ' character" :
        "missing terminating \" character";
    s.report_error(text)
        .add_primary(s.location(opening_quote, opening_quote + 1), text)
        .add_supplement(s.current_token_location());
}

/// Tokenizes a single character (token::CHAR).
void tokenize_character(tokenization_state& s) {
    // skip over opening quote
    source_iterator opening_quote = s.next;
    ++s.next;

    // set the tokenization iterator to the end of the quoted content
    source_view quoted_content = detail::quoted_content<'\''>(s.next, s.end);
    s.next = quoted_content.end();

    // ensure that the quoted content ends with a terminating quote
    if (!s.next_is('\'')) {
        report_missing_terminating_quote<'\''>(s, opening_quote);
        s.push_dummy(token::CHAR);
        return;
    }

    // consume the terminating quote
    ++s.next;

    // a character literal cannot be empty!
    if (quoted_content.empty()) {
        s.report_error("empty character literal");
        s.push_dummy(token::CHAR);
        return;
    }

    // consume a character from the quoted content
    source_iterator consume_end;
    std::optional<char_t> char_value =
        consume_char<'\''>(s, quoted_content, consume_end);

    if (!char_value) {
        // detail::consume_char already reported an error, so just push
        // token::CHAR with the dummy error value and return
        s.push_dummy(token::CHAR);
        return;
    }

    // a character literal must contain exactly one character!
    if (consume_end != quoted_content.end()) {
        s.report_error("character literal contains more than one character")
            .add_supplement(
                s.location(quoted_content),
                "more than one character in literal"
            )
            .add_primary(
                s.location(opening_quote, opening_quote + 1),
                "use \" quotes if you meant to use a string"
            );
        s.push_dummy(token::CHAR);
        return;
    }

    s.push<token::CHAR>(*char_value);
}

/**
 * Tokenizes the upcoming characters as a token::STRING, up to a terminating
 * double-quote `"` or left-brace `{`.
 *
 * Entering this function necessarily means that we're currently in a string
 * context, i.e., the following preconditions hold:
 * ~~~{.cpp}
 * s.string_interpolation_stack.empty() == false;
 * s.string_interpolation_stack.current_frame().open_left_braces == 0;
 * ~~~
 *
 * If the string is empty, then no token::STRING will be pushed.
 */
static void tokenize_string(tokenization_state& s) {
    // set the tokenization iterator to the end of the quoted content
    source_view quoted_content = detail::quoted_content<'"'>(s.next, s.end);
    s.next = quoted_content.end();

    // ensure that the quoted content ends with a terminating character
    if (!s.next_is('"') && !s.next_is('{')) {
        source_iterator opening_quote =
            s.string_interpolation_stack.current_frame().opening_quote;
        report_missing_terminating_quote<'"'>(s, opening_quote);
        if (!quoted_content.empty()) {
            s.push_dummy(token::STRING);
        }
        return;
    }

    // if the quoted content is empty, do nothing
    if (quoted_content.empty()) { return; }

    // parse the quoted content into the string token's `value`.
    token_attribute_t<token::STRING> value;
    value.reserve(quoted_content.size());
    while (!quoted_content.empty()) {
        // consume a character from the quoted content
        source_iterator consume_end;
        std::optional<char_t> char_value =
            consume_char<'"'>(s, quoted_content, consume_end);
        quoted_content = source_view(consume_end, quoted_content.end());

        if (!char_value) {
            // detail::consume_char already reported an error, so just push
            // token::STRING with the dummy error value and return
            s.push_dummy(token::STRING);
            return;
        }

        value += char(*char_value);
    }

    s.push<token::STRING>(std::move(value));
}

void tokenize_double_quote(tokenization_state& s) {
    if (s.string_interpolation_stack.in_string_context()) {
        // we're in a string context, so `s.next` is a closing-quote
        s.string_interpolation_stack.pop();
        s.consume_and_push(token::QUOTE);
    } else {
        // we're not in a string context, so `s.next` is an opening-quote
        s.string_interpolation_stack.push(s.next);
        s.consume_and_push(token::QUOTE);
        s.begin_next_token();
        tokenize_string(s);
    }
}

void tokenize_left_brace(tokenization_state& s) {
    s.consume_and_push(token::L_BRACE);
    if (!s.string_interpolation_stack.empty()) {
        s.string_interpolation_stack.current_frame().open_left_braces += 1;
    }
}

void tokenize_right_brace(tokenization_state& s) {
    s.consume_and_push(token::R_BRACE);
    auto& sis = s.string_interpolation_stack;
    if (!sis.empty()) {
        sis.current_frame().open_left_braces -= 1;
        if (sis.current_frame().open_left_braces == 0) {
            // back to string context! Woohoo!
            s.begin_next_token();
            tokenize_string(s);
        }
    }
}

} // namespace fp::lex::detail
