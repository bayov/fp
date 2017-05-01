#pragma once

#include <fp/common/types.h>
#include <fp/common/input.h>
#include <fp/common/diagnostic_report.h>
#include <fp/lex/token_list.h>

namespace fp::lex::detail {

/// The internal state of a fp::lex::detail::tokenizer.
class tokenizer_state {
public:

    symbol_iterator it;     ///< The current symbol.
    symbol_iterator end;    ///< The end of the input.

    /**
     * This stack indicates the current tokenizing position in relation to
     * string interpolations. For example, a stack of size 1 we are currently
     * tokenizing inside a string interpolation:
     *
     *      "one plus one plus million is {1 + 1 + 1`000`000}"
     *                                    |--(we are here)--|
     *
     * While a stack of size 2 means we are inside a second string
     * interpolation:
     *
     *      "hello, {"from the other {"side of the plant"}..."}"
     *              |-(depth 1)------|                   |----|
     *                               |-(depth 2)---------|
     *
     * A stack of size zero, of course, means we are not inside any string
     * interpolation.
     *
     * Additionally, each element in the stack (`size_t`) keeps track of how
     * many non-string-interpolation left-braces are currently open.
     * Encountering will pop the current string interpolation frame from the
     * stack only when there are 0 open left-braces:
     *
     *      "look, {"a wild brace:" { 3 { 4 } 1 + 1 } "bla" }"
     *             |----------------v---v---v-------v-------|
     *               open braces:   1   2   1       0
     */
    std::deque<size_t> string_iterpolation_stack;

    tokenizer_state(
        const input_view& input,
        token_list& output_token_list,
        diagnostic_report& diagnostics
    ) :
        it(input.begin()),
        end(input.end()),
        m_tokens(output_token_list),
        m_diagnostics(diagnostics),
        m_token(it),
        m_line(it)
    {}

    /// Report a diagnostic error with the symbols of the current token.
    void error(std::string what = "Invalid symbol") const {
        error(m_token, it + 1, std::move(what));
    }

    /// Report a diagnostic error with symbols `[from, to)`.
    void error(
        symbol_iterator from,
        symbol_iterator to,
        std::string what = "Invalid symbol"
    ) const {
        m_diagnostics.add(diagnostic::error(
            source_location({ from, to }, m_line, m_line_number),
            std::move(what)
        ));
    }

    /// @return The current token's symbols.
    input_view token_symbols() { return { m_token, it }; }

    /// Advance one symbol and start a new-line.
    void newline() {
        ++it;
        m_line = it;
        ++m_line_number;
    }

    /// @return `true` if the upcoming symbols are `SYMBOLS...`.
    template <symbol_t... SYMBOLS>
    bool next_is() const {
        using indices = std::make_index_sequence<sizeof...(SYMBOLS)>;
        return next_is_impl<SYMBOLS...>(indices{});
    }

    /// Push a new token to the list, with `args` forwarded to its attribute.
    template <token TOKEN, class... Args>
    void push(Args&&... args) {
        m_tokens.push_back<TOKEN>(
            source_location(token_symbols(), m_line, m_line_number),
            attribute_t<TOKEN>(std::forward<Args>(args)...)
        );
        m_token = it;
    }

    /// Push a new token to the list, with @ref no_attribute.
    void push(token t) {
        m_tokens.push_back(
            t,
            source_location(token_symbols(), m_line, m_line_number)
        );
        m_token = it;
    }

    /// Tokenize the current symbol as `TOKEN`.
    template <token TOKEN>
    void tokenize_as() {
        ++it;
        push<TOKEN>();
    }

    /// Skip to the next `'\n'` or `'\r'`.
    void skip_to_end_of_line() {
        while (it != end && *it != '\n' && *it != '\r') { ++it; }
    }

private:

    token_list& m_tokens;
    diagnostic_report& m_diagnostics;

    symbol_iterator m_token;    ///< The beginning of the current token.
    symbol_iterator m_line;     ///< The beginning of the current line.
    size_t m_line_number = 1;   ///< The current line number.

    /// @see next_is()
    template <symbol_t... SYMBOLS, size_t... INDICES>
    bool next_is_impl(std::index_sequence<INDICES...>) const {
        if (it + sizeof...(SYMBOLS) >= end) { return false; }
        return (... && (*(it + 1 + INDICES) == SYMBOLS));
    }

};

} // fp::lex::detail
