#pragma once

#include <string_view>

namespace fp::error {

/**
 * Represents a type of compiler error.
 *
 * Preferably, all diagnostic errors reported by the compiler should use one of
 * the error codes defined below.
 */
struct code {
    std::string_view code;
    std::string_view brief;
};

inline code E0001_stray_character{"E0001", "stray character in source code"};

inline code E0002_missing_terminating_single_quote{
    "E0002", "missing terminating ' character"
};

inline code E0003_missing_terminating_double_quote{
    "E0003", "missing terminating \" character"
};

inline code E0004_empty_character_literal{"E0004", "empty character literal"};

inline code E0005_invalid_escape_sequence{"E0005", "invalid escape sequence"};

inline code E0006_character_literal_with_more_than_one{
    "E0006",
    "character literal contains more than one character"
};

inline code E0007_invalid_number_literal{"E0007", "invalid number literal"};

inline code E0008_unsupported_float_base{
    "E0008",
    "unsupported floating-number base"
};

inline code E0009_stray_exclamation_mark{"E0009", "stray exclamation mark"};

} // namespace fp::error
