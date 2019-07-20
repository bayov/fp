#pragma once

#include <fp/literal_types.h>
#include <fp/source_code.h>
#include <fp/diagnostic/report.h>
#include <fp/lex/tokenized_list.h>
#include <fp/lex/detail/string_interpolation_stack.h>

namespace fp::lex::detail {

/// The internal state being kept during tokenization.
struct tokenization_state {
    source_view     source; ///< The source code being tokenized.
    source_iterator next;   ///< Points to the next character in the source.
    source_iterator end;    ///< Points to the end of the source.

    /// See detail::string_interpolation_stack for details.
    detail::string_interpolation_stack string_interpolation_stack;

    tokenization_state(
        source_view source,
        tokenized_list& output_tokens_list,
        diagnostic::report& report
    ) :
        source(source),
        next(source.begin()),
        end(source.end()),
        tokens_(output_tokens_list),
        report_(report),
        token_begin_(next),
        line_begin_(next)
    {}

    //@{
    /// Reports a diagnostic::error for the given source code section.
    diagnostic::problem& report_error(
        source_view source_section,
        std::string text
    ) {
        report_problem(
            diagnostic::error(location(source_section), std::move(text))
        );
        return report_.errors().back();
    }
    diagnostic::problem& report_error(
        source_iterator from,
        source_iterator to,
        std::string text
    ) {
        return report_error(make_source_view(from, to), std::move(text));
    }
    //@}

    /// Reports a diagnostic::error for the current token.
    diagnostic::problem& report_error(std::string text) {
        return report_error(token_begin_, next, std::move(text));
    }

    /// Report the given diagnostic::problem.
    void report_problem(diagnostic::problem p) { report_.add(std::move(p)); }

    //@{
    /**
     * Returns the source location of the given source code section, filling in
     * missing details using available line information.
     */
    source_location location(source_view source_section) {
        return source_location {
            .chars = source_section,
            .source_code = source,
            .line = line_begin_,
            .line_number = line_number_
        };
    }
    source_location location(source_iterator from, source_iterator to) {
        return location(make_source_view(from, to));
    }
    //}

    /// Returns the source section of the current token.
    source_view current_token_characters() {
        return make_source_view(token_begin_, next);
    }

    /// Returns the source location of the current token.
    source_location current_token_location() {
        return location(current_token_characters());
    }

    /**
     * Indicates that the next character is the beginning of the next token that
     * will be tokenized.
     */
    void begin_next_token() { token_begin_ = next; }

    /// Indicates that the next character is the beginning of a new line.
    void begin_new_line() {
        line_begin_ = next;
        ++line_number_;
    }

    /// Returns `true` if the the next character in the source is `c`.
    bool next_is(source_char c) const { return next != end && *next == c; }

    /// Returns `true` if the the next characters in the source are `chars`.
    bool next_is(source_view chars) const {
        return make_source_view(next, end).starts_with(chars);
    }

    /// Push the token to the output list (token_attribute_t must be void).
    void push(token t) {
        tokens_.push_back({
            .token = t,
            .dummy = false,
            .source_location = current_token_location()
        });
    }

    /// Push `TOKEN` to the output list with the given `attribute` attached.
    template <token TOKEN>
    void push(token_attribute_t<TOKEN> attribute) {
        tokens_.push_back({
            .token = TOKEN,
            .dummy = false,
            .attribute = std::move(attribute),
            .source_location = current_token_location()
        });
    }

    /// Push a dummy error `TOKEN`.
    void push_dummy(token t) {
        tokens_.push_back({
            .token = t,
            .dummy = true,
            .source_location = current_token_location()
        });
    }

    /// Consume the next character and tokenize it as the given token.
    void consume_and_push(token t) {
        ++next;
        push(t);
    }

private:
    tokenized_list& tokens_; ///< The list of tokens produced so far.

    /// Any problems encountered during tokenization should be reported here.
    diagnostic::report& report_;

    /**
     * Points to the beginning of the current token.
     *
     * When the next character (tokenization_state::next) signals the start of a
     * new token, tokenization_state::begin_next_token() should be called to
     * update this variable.
     */
    source_iterator token_begin_;

    /**
     * Points to the beginning of the current line.
     *
     * After consuming a newline character, this iterator needs to be updated by
     * calling tokenization_state::begin_new_line().
     */
    source_iterator line_begin_;

    size_t line_number_ = 1; ///< Holds the current line's number.
};

} // namespace fp::lex::detail
