#pragma once

#include <string>

#include <fp/common/types.h>

namespace fp::lex::detail {

/// A compile-time range of symbols.
template <symbol_t FROM, symbol_t TO>
struct symbol_range {

    /// @return `true` if the given symbol is inside the range.
    static bool contain(symbol_t s) { return FROM <= s && s <= TO; }

    /// @return A string representation of the range.
    static std::string as_string() { return FROM + std::string("-") + TO; }

};

/// Contains multiple compile-time symbol ranges (@ref symbol_range).
template <class... SymbolRanges>
struct composite_symbol_range {

    /// @return `true` if the given symbol is contained in any of the ranges.
    static bool contain(symbol_t s) {
        return (... || SymbolRanges::contain(s));
    }

    /// @return A string representation of the range.
    static std::string as_string() {
        auto result = (... + (SymbolRanges::as_string() + ' '));
        result.pop_back();
        return result;
    }

};

} // fp::lex::detail
