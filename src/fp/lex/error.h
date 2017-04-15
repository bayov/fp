#pragma once

#include <stdexcept>

#include "symbol.h"

namespace fp::lex {

/// Represents an error in lexical analysis.
class error : public std::exception {
public:

    const input_view_t symbols;     ///< The input that caused the error.
    const symbol_iterator line;     ///< The beginning of the current line.
    const size_t line_number;       ///< The current line number.

    error(
        input_view_t symbols,
        symbol_iterator line,
        size_t line_number,
        std::string what
    ) :
        symbols(std::move(symbols)),
        line(line),
        line_number(line_number),
        m_what(std::move(what))
    {}

    const char* what() const noexcept override { return m_what.c_str(); }

private:

    std::string m_what;

};

} // namespace fp::lex
