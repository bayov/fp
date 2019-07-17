#pragma once

#include <deque>

#include <fp/literal_types.h>
#include <fp/source_code.h>
#include <fp/diagnostic/report.h>
#include <fp/lex/tokenized_list.h>

namespace fp::lex::detail {

/// The internal state being kept during tokenization.
struct tokenization_state {
    source_view     source; ///< The source code being tokenized.
    source_iterator next;   ///< Points to the next character in the source.
    source_iterator end;    ///< Points to the end of the source.

    /**
     * This stack keeps tracks of our current string interpolation "frame".
     *
     * For example, a stack of size 1 means we are currently inside a string
     * interpolation:
     *
     *      "one plus one plus million is {1 + 1 + 1`000`000}"
     *                                    |--(we are here)--|
     *
     * While a stack of size 2 means we are inside a second string
     * interpolation:
     *
     *      "hello, { "from the other {"side of the plant"}..."} "
     *              |-(depth 1)-------|                   |-----|
     *                                |-(depth 2)---------|
     *
     * A stack of size zero, of course, means we are not inside any string
     * interpolation.
     *
     * Additionally, each element in the stack (`size_t`) keeps track of how
     * many non-string-interpolation left-braces are currently open.
     * Encountering a right-brace will pop the current string interpolation
     * frame from the stack only when there are 0 open left-braces:
     *
     *      "look, {"a wild brace:" { 3 { 4 } 1 + 1 } "bla" }"
     *             |----------------v---v---v-------v-------|
     *               open braces:   1   2   1       0
     */
    std::deque<size_t> string_interpolation_stack;

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

    /// Reports a diagnostic::error for the current token.
    void report_error(std::string text) {
        report_error(token_begin_, next, std::move(text));
    }

    /// Reports a diagnostic::error for characters `[from, to)`.
    void report_error(
        source_iterator from,
        source_iterator to,
        std::string text
    ) {
        report_problem(diagnostic::error(location(from, to), std::move(text)));
    }

    /// Report the given diagnostic::problem.
    void report_problem(diagnostic::problem p) { report_.add(std::move(p)); }

    /// Returns the source location of the current token.
    source_location current_token_location() {
        return location(token_begin_, next);
    }

    /// Returns the source location of `[from, to)` in the current line.
    source_location location(source_iterator from, source_iterator to) {
        return source_location {
            .chars = make_source_view(from, to),
            .source_code = source,
            .line = line_begin_,
            .line_number = line_number_
        };
    }

//    /// @return The current token's symbols.
//    input_view token_symbols() const { return { m_token, it }; }

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

    /// Returns `true` if the next characters in the source are exactly `CHARS`.
    template <source_char... CHARS>
    bool next_is() const {
        if (next + sizeof...(CHARS) > end) { return false; }
        using indices = std::make_index_sequence<sizeof...(CHARS)>;
        return next_is_impl<CHARS...>(indices{});
    }

//    /// Push a new token to the list, with `args` forwarded to its attribute.
//    template <token TOKEN, class... Args>
//    void push(Args&&... args) {
//        m_tokens.push_back<TOKEN>(
//            location(),
//            attribute_t<TOKEN>(std::forward<Args>(args)...)
//        );
//    }

    /// Push `TOKEN` to the output list (token_attribute_t<TOKEN> must be void).
    template <token TOKEN>
    void push() {
        static_assert(
            std::is_void_v<token_attribute_t<TOKEN>>,
            "The given `TOKEN` has a non-empty attribute."
        );
        tokens_.push_back({
            .token = TOKEN,
            .source_location = current_token_location()
        });
    }

    /// Push `TOKEN` to the output list with the given `attribute` attached.
    template <token TOKEN>
    void push(token_attribute_t<TOKEN> attribute) {
        tokens_.push_back({
            .token = TOKEN,
            .attribute = std::move(attribute),
            .source_location = current_token_location()
        });
    }

    /// Consume the next character and tokenize it as `TOKEN`.
    template <token TOKEN>
    void consume_and_push() {
        ++next;
        push<TOKEN>();
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

    template <source_char... CHARS, size_t... INDICES>
    bool next_is_impl(std::index_sequence<INDICES...>) const {
        return (... && (*(next + INDICES) == CHARS));
    }
};

} // namespace fp::lex::detail
