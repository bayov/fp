#pragma once

#include <fp/literal_types.h>
#include <fp/error_codes.h>
#include <fp/source_code.h>
#include <fp/diagnostic/report.h>
#include <fp/lex/tokenized_list.h>
#include <fp/lex/detail/string_interpolation_stack.h>

namespace fp::lex::detail {

/// The internal state being kept during tokenization.
struct tokenization_state {
    const source_file& file; ///< The source file being tokenized.
    source_iterator    next; ///< Points to the next character in the source.
    source_iterator    end;  ///< Points to the end of the source.

    /// See detail::string_interpolation_stack for details.
    detail::string_interpolation_stack string_interpolation_stack;

    tokenization_state(
        const source_file& file,
        tokenized_list& output_tokens_list,
        diagnostic::report& report
    ) :
        file(file),
        next(file.content.begin()),
        end(file.content.end()),
        tokens(output_tokens_list),
        report(report),
        token_begin(next),
        line_begin(next)
    {}

    /// Reports a diagnostic::error with the given error::code.
    diagnostic::problem& report_error(const error::code* error_code) {
         report_problem(diagnostic::error(error_code));
         return report.errors().back();
    }

    /// Reports a diagnostic::error with the given `text`.
    diagnostic::problem& report_error(std::string text) {
         report_problem(diagnostic::error(std::move(text)));
         return report.errors().back();
    }

    /// Reports the given diagnostic::problem.
    diagnostic::problem& report_problem(diagnostic::problem p) {
        return report.add(std::move(p));
    }

    //@{
    /**
     * Returns the source location of the given source code section, filling in
     * missing details using available line information.
     */
    source_location location(source_view source_section) {
        return source_location {
            .chars = source_section,
            .file = file,
            .line = line_begin,
            .line_number = line_number
        };
    }
    source_location location(source_iterator from, source_iterator to) {
        return location(source_view(from, to));
    }
    //}

    /// Returns the source section of the current token.
    source_view current_token_characters() {
        return { token_begin, next};
    }

    /// Returns the source location of the current token.
    source_location current_token_location() {
        return location(current_token_characters());
    }

    /**
     * Indicates that the next character is the beginning of the next token that
     * will be tokenized.
     */
    void begin_next_token() { token_begin = next; }

    /// Indicates that the next character is the beginning of a new line.
    void begin_new_line() {
        line_begin = next;
        ++line_number;
    }

    /// Returns `true` if the the next character in the source is `c`.
    bool next_is(char c) const { return next != end && *next == c; }

    /// Returns `true` if the the next characters in the source are `chars`.
    bool next_is(source_view chars) const {
        return source_view(next, end).starts_with(chars);
    }

    /// Push the token to the output list (token_attribute_t must be void).
    void push(token t) {
        tokens.push_back({
            .token = t,
            .dummy = false,
            .source_location = current_token_location()
        });
    }

    /// Push `TOKEN` to the output list with the given `attribute` attached.
    template <token TOKEN>
    void push(token_attribute_t<TOKEN> attribute) {
        tokens.push_back({
            .token = TOKEN,
            .dummy = false,
            .attribute = std::move(attribute),
            .source_location = current_token_location()
        });
    }

    /// Push a dummy error `TOKEN`.
    void push_dummy(token t, lex::attribute_t attribute = {}) {
        tokens.push_back({
            .token = t,
            .dummy = true,
            .attribute = std::move(attribute),
            .source_location = current_token_location()
        });
    }

    /// Consume the next character and tokenize it as the given token.
    void consume_and_push(token t) {
        ++next;
        push(t);
    }

private:
    tokenized_list& tokens; ///< The list of tokens produced so far.

    /// Any problems encountered during tokenization is reported here.
    diagnostic::report& report;

    /**
     * Points to the beginning of the current token.
     *
     * When the next character (tokenization_state::next) signals the start of a
     * new token, tokenization_state::begin_next_token() should be called to
     * update this variable.
     */
    source_iterator token_begin;

    /**
     * Points to the beginning of the current line.
     *
     * After consuming a newline character, this iterator needs to be updated by
     * calling tokenization_state::begin_new_line().
     */
    source_iterator line_begin;

    size_t line_number = 1; ///< Holds the current line's number.
};

} // namespace fp::lex::detail
