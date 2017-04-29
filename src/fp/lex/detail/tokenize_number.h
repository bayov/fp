#pragma once

#include "tokenizer_state.h"
#include "identifier_symbols.h"

namespace fp::lex::detail {

/// Throw an error for a missing digit. Takes a symbol range.
template <class SymbolRange>
void digit_error(tokenizer_state& s, symbol_iterator from, symbol_iterator to) {
    s.error(from, to, "Expected a digit: " + SymbolRange::as_string());
}

template <class Digits, class ParseDigit>
void tokenize_number_literal(tokenizer_state& s, ParseDigit parse_digit) {
    integer_type value = 0;
    bool expecting_digit = true;
    bool overflow = false;
    for (; s.it != s.end; ++s.it) {
        if (expecting_digit && !Digits::contain(*s.it)) {
            digit_error<Digits>(s, s.it, s.it);
        }
        if (*s.it == '`') {
            expecting_digit = true;
            continue;
        }
        if (!Digits::contain(*s.it)) {
            if (identifier_symbols::contain(*s.it)) {
                digit_error<Digits>(s, s.it, s.it + 1);
            }
            if (overflow) {
                s.error("Literal number is too big (will overflow)");
            }
            s.push<token::INTEGER>(value);
            return;
        }
        auto previous_value = value;
        parse_digit(*s.it, value);
        if (value < previous_value) { overflow = true; }
        expecting_digit = false;
    }
    if (expecting_digit) { digit_error<Digits>(s, s.it, s.it); }
}

inline void tokenize_hex_literal(tokenizer_state& s) {
    s.it += 2; // skip over `0x` prefix
    using digits = composite_symbol_range<
        symbol_range<'0', '9'>,
        symbol_range<'a', 'f'>,
        symbol_range<'A', 'F'>
    >;
    tokenize_number_literal<digits>(s, [](symbol_t symbol, integer_type& v) {
        integer_type d;
        if (symbol <= '9') {
            d = integer_type(symbol - '0');         // 0-9
        } else if (symbol >= 'a') {
            d = integer_type(symbol - 'a') + 10;    // a-f
        } else {
            d = integer_type(symbol - 'A') + 10;    // A-F
        }
        v = (v << 4) | d;
    });
}

inline void tokenize_octal_literal(tokenizer_state& s) {
    s.it += 2; // skip over `0o` prefix
    using digits = symbol_range<'0', '7'>;
    tokenize_number_literal<digits>(s, [](symbol_t symbol, integer_type& v) {
        v = (v << 3) | (symbol - '0');
    });
}

inline void tokenize_binary_literal(tokenizer_state& s) {
    s.it += 2; // skip over `0b` prefix
    using digits = symbol_range<'0', '1'>;
    tokenize_number_literal<digits>(s, [](symbol_t symbol, integer_type& v) {
        v = (v << 1) | (symbol - '0');
    });
}

inline void tokenize_decimal_literal(tokenizer_state& s) {
    using digits = symbol_range<'0', '9'>;
    tokenize_number_literal<digits>(s, [](symbol_t symbol, integer_type& v) {
        v = (v * 10) + (symbol - '0');
    });
}

/**
 * Tokenize the upcoming symbols as a floating-type literal (token::FLOAT).
 *
 * @todo Parse manually, instead of using std::strtod. (not easy...)
 */
inline void tokenize_floating_literal(tokenizer_state& s) {
    using digits = symbol_range<'0', '9'>;

    // first, ensure that the floating literal is well-formed.
    bool decimal_mark_seen = false;
    bool exponent_seen = false;
    for (; s.it != s.end; ++s.it) {
        if (*s.it == '`') {
            s.error(
                s.it, s.it + 1,
                "Currently, ` marks inside floating-point literals are not "
                "supported. This feature will be added in the future."
            );
        }
        if (*s.it == '.') {
            if (decimal_mark_seen) {
                s.error(s.it, s.it + 1, "Second decimal mark");
            }
            decimal_mark_seen = true;
            continue;
        }
        if (*s.it == 'e' || *s.it == 'E') {
            if (exponent_seen) {
                s.error(s.it, s.it + 1, "Encountered a second exponent");
            }
            exponent_seen = true;
            if (*s.it == '+' || *s.it == '-') { // allow sign after exponent
                ++s.it;
                if (s.it == s.end || !digits::contain(*s.it)) {
                    digit_error<digits>(s, s.it, s.it);
                }
            }
            continue;
        }
        if (!digits::contain(*s.it)) {
            if (identifier_symbols::contain(*s.it)) {
                digit_error<digits>(s, s.it, s.it + 1);
            }
            break;
        }
    }

    // From this point, we know that `[s.token, s.it)` is a well-formed float

    // since we are using std::strtod, we cannot control when it stops
    // parsing if the floating-point literal is at the end of the input.
    // We can't assume that the input string ends with '\0', so for now we
    // must throw an error here.
    if (s.it == s.end) {
        s.error(
            "Real literals at the end of the input are not yet supported.\n"
            "This is a technical issue that will be solved in the future."
        );
    }

    float_type value = std::strtod(&*s.token, nullptr);
    if (errno == ERANGE) {
        errno = 0;
        if (value == 0) {
            s.error(
                "Literal number is too small (will be truncated to zero).\n"
            );
        } else {
            s.error("Literal number is too big (will overflow).\n");
        }
    }

    s.push<token::FLOAT>(value);
}

/// Tokenize a decimal number or a floating-point number.
inline void tokenize_decimal_or_floating(tokenizer_state& s) {
    using decimal_symbols = composite_symbol_range<
        symbol_range<'0', '9'>,
        symbol_range<'`', '`'>
    >;

    // skip to first non-decimal symbol
    auto it = s.it + 1; // we already know that the first number is a digit
    while (it != s.end && decimal_symbols::contain(*it)) { ++it; }

    if (it != s.end && (*it == '.' || *it == 'e' || *it == 'E')) {
        tokenize_floating_literal(s);
    } else {
        tokenize_decimal_literal(s);
    }
}

/// Tokenize a number (either token::INTEGER or token::FLOAT).
inline void tokenize_number(tokenizer_state& s) {
    if (*s.it != '0' || s.it + 1 == s.end) {
        tokenize_decimal_or_floating(s);
        return;
    }
    switch (*(s.it + 1)) {
        case 'x':
            tokenize_hex_literal(s);
            break;
        case 'o':
            tokenize_octal_literal(s);
            break;
        case 'b':
            tokenize_binary_literal(s);
            break;
        default:
            tokenize_decimal_or_floating(s);
            break;
    }
}

} // fp::lex::detail
