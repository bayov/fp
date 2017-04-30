#pragma once

#include <fp/common/types.h>
#include <fp/common/input.h>
#include <fp/common/diagnostic.h>
#include <fp/lex/token_list.h>

namespace fp::lex::detail {

/// The internal state of a fp::lex::detail::tokenizer.
struct tokenizer_state {

    token_list tokens;      ///< The current token list.
    symbol_iterator it;     ///< The current symbol.
    symbol_iterator end;    ///< The end of the input.
    symbol_iterator token;  ///< The beginning of the current token.
    symbol_iterator line;   ///< The beginning of the current line.
    size_t line_number;     ///< The current line number.

    /// Initialize the state to start tokenizing the given input.
    void initialize(const input_view& input) {
        tokens = token_list();
        it = input.begin();
        end = input.end();
        token = it;
        line = it;
        line_number = 1;
    }

    /// Throw an error with the symbols of the current token being parsed.
    void error(std::string what = "Invalid symbol") const {
        error(token, it + 1, std::move(what));
    }

    /// Throw an error with the symbols `[from, to)`.
    void error(
        symbol_iterator from,
        symbol_iterator to,
        std::string what = "Invalid symbol"
    ) const {
        throw diagnostic::error(
            source_location({ from, to }, line, line_number),
            std::move(what)
        );
    }

    /// Advance one symbol and start a new-line.
    void newline() {
        ++it;
        line = it;
        ++line_number;
    }

    /// @see next_is()
    template <symbol_t... SYMBOLS, size_t... INDICES>
    bool next_is_impl(std::index_sequence<INDICES...>) const {
        if (it + sizeof...(SYMBOLS) >= end) { return false; }
        return (... && (*(it + 1 + INDICES) == SYMBOLS));
    }

    /// @return `true` if the upcoming symbols are `SYMBOLS...`.
    template <symbol_t... SYMBOLS>
    bool next_is() const {
        using indices = std::make_index_sequence<sizeof...(SYMBOLS)>;
        return next_is_impl<SYMBOLS...>(indices{});
    }

    /// Push a new token to the list, with `args` forwarded to its attribute.
    template <lex::token TOKEN, class... Args>
    void push(Args&&... args) {
        tokens.push_back<TOKEN>(
            source_location(token_symbols(), line, line_number),
            attribute_t<TOKEN>(std::forward<Args>(args)...)
        );
    }

    /// Push a new token to the list, with @ref no_attribute.
    void push(lex::token t) {
        tokens.push_back(t, source_location(token_symbols(), line, line_number));
    }

    /// Tokenize the current symbol as `TOKEN`.
    template <lex::token TOKEN>
    void tokenize_as() {
        ++it;
        push<TOKEN>();
    }

    /// Skip to the next `'\n'` or `'\r'`.
    void skip_to_end_of_line() {
        while (it != end && *it != '\n' && *it != '\r') { ++it; }
    }

    /// @return An @ref input_view_t to the current token's symbols.
    input_view token_symbols() { return { token, it }; }

};

} // fp::lex::detail
