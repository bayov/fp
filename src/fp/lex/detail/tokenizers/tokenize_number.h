#pragma once

#include <fp/lex/detail/tokenizer_state.h>
#include <fp/lex/detail/identifier_symbols.h>

namespace fp::lex::detail {

using skippable_digits = composite_symbol_range<
    identifier_symbols,
    symbol_range<'`', '`'>,
    symbol_range<'.', '.'>
>;

/**
 * It will be much too messy to report more than one error on a single number,
 * so in case we encounter an error, we shall skip these symbols.
 */
void skip_digits(tokenizer_state& s) {
    while (s.it != s.end && skippable_digits::contain(*s.it)) { ++s.it; }
}

/// Like @ref skip_digits, but for floating literals.
void skip_floating_digits(tokenizer_state& s) {
    while (s.it != s.end) {
        if (skippable_digits::contain(*s.it)) {
            ++s.it;
        } else if (*s.it == 'e' || *s.it == 'e') {
            ++s.it;
            if (*s.it == '+' || *s.it == '-') { ++s.it; }
        } else {
            break;
        }
    }
}

struct digit_error : compilation_error {};

/// Report a diagnostic error for an invalid number digit (and throw).
inline void invalid_digit(
    tokenizer_state& s,
    std::string text,
    void (*skip)(tokenizer_state& s) = skip_digits
) {
    // if the current symbol is a valid digit candidate, mark it as the part of
    // the source of the error
    auto source = skippable_digits::contain(*s.it) ?
                  s.location(s.it, s.it + 1) : s.location(s.it, s.it);

    // build a diagnostic error, with the entire number symbols as supplement
    auto d = diagnostic::error(source, std::move(text));
    skip(s);
    d.add_supplement(s.location());

    s.report(std::move(d));
    s.push<token::ERROR>();
    throw digit_error();
}

/// Report a diagnostic error for a missing digit (and throws).
template <class SymbolRange>
void missing_digit(
    tokenizer_state& s,
    void (*skip)(tokenizer_state& s) = skip_digits
) {
    invalid_digit(s, "Expected a digit: " + SymbolRange::as_string(), skip);
}

template <class Digits, class ParseDigit>
void tokenize_integer_literal(tokenizer_state& s, ParseDigit parse_digit) {
    integer_type value = 0;
    bool expecting_digit = true;
    bool overflow = false;
    for (; s.it != s.end; ++s.it) {
        if (expecting_digit && !Digits::contain(*s.it)) {
            missing_digit<Digits>(s);
        }
        if (*s.it == '`') {
            expecting_digit = true;
            continue;
        }
        if (!Digits::contain(*s.it)) {
            if (expecting_digit || skippable_digits::contain(*s.it)) {
                missing_digit<Digits>(s);
            }
            if (overflow) { s.error("Integer is too big (will overflow)"); }
            s.push<token::INTEGER>(value);
            return;
        }
        auto previous_value = value;
        parse_digit(*s.it, value);
        if (value < previous_value) { overflow = true; }
        expecting_digit = false;
    }
}

inline void tokenize_hex_literal(tokenizer_state& s) {
    s.it += 2; // skip over `0x` prefix
    using digits = composite_symbol_range<
        symbol_range<'0', '9'>,
        symbol_range<'a', 'f'>,
        symbol_range<'A', 'F'>
    >;
    tokenize_integer_literal<digits>(
        s, [](symbol_t symbol, integer_type& v) {
            integer_type d;
            if (symbol <= '9') {
                d = integer_type(symbol - '0');         // 0-9
            } else if (symbol >= 'a') {
                d = integer_type(symbol - 'a') + 10;    // a-f
            } else {
                d = integer_type(symbol - 'A') + 10;    // A-F
            }
            v = (v << 4) | d;
        }
    );
}

inline void tokenize_octal_literal(tokenizer_state& s) {
    s.it += 2; // skip over `0o` prefix
    using digits = symbol_range<'0', '7'>;
    tokenize_integer_literal<digits>(
        s, [](symbol_t symbol, integer_type& v) {
            v = (v << 3) | (symbol - '0');
        }
    );
}

inline void tokenize_binary_literal(tokenizer_state& s) {
    s.it += 2; // skip over `0b` prefix
    using digits = symbol_range<'0', '1'>;
    tokenize_integer_literal<digits>(
        s, [](symbol_t symbol, integer_type& v) {
            v = (v << 1) | (symbol - '0');
        }
    );
}

inline void tokenize_decimal_literal(tokenizer_state& s) {
    using digits = symbol_range<'0', '9'>;
    tokenize_integer_literal<digits>(
        s, [](symbol_t symbol, integer_type& v) {
            v = (v * 10) + (symbol - '0');
        }
    );
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
            // TODO: until we parse manually, we can at least allow ` by copying
            //       the input and removing all occurrences of '`'
            invalid_digit(
                s,
                "Currently, ` marks inside floating-point literals are not "
                "supported. This feature will be added in the future.",
                skip_floating_digits
            );
        }
        if (*s.it == '.') {
            if (decimal_mark_seen) {
                invalid_digit(s, "Second decimal mark", skip_floating_digits);
            }
            decimal_mark_seen = true;
            continue;
        }
        if (*s.it == 'e' || *s.it == 'E') {
            if (exponent_seen) {
                invalid_digit(s, "Second exponent mark", skip_floating_digits);
            }
            exponent_seen = true;
            if (*s.it == '+' || *s.it == '-') { // allow sign after exponent
                ++s.it;
                if (s.it == s.end || !digits::contain(*s.it)) {
                    missing_digit<digits>(s, skip_floating_digits);
                }
            }
            continue;
        }
        if (!digits::contain(*s.it)) {
            if (skippable_digits::contain(*s.it)) {
                missing_digit<digits>(s, skip_floating_digits);
            }
            break;
        }
    }

    // From this point, we know that `[s.token, s.it)` is a well-formed float

    // since we are using std::strtod, we cannot control when it stops
    // parsing if the floating-point literal is at the end of the input.
    // We can't assume that the input string ends with '\0', so for now we
    // must report an error here.
    if (s.it == s.end) {
        invalid_digit(
            s,
            "Real literals at the end of the input not supported. "
            "This is a technical issue that will be solved in the future.",
            skip_floating_digits
        );
    }

    float_type value = std::strtod(&s.token_symbols().front(), nullptr);
    if (errno == ERANGE) {
        errno = 0;
        if (value == 0) {
            s.error("Literal number is too small (will be truncated to zero).");
        } else {
            s.error("Literal number is too big (will overflow).");
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
    try {
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
    } catch (const digit_error&) {
        // May be thrown during number parsing. It is already reported, so we
        // can safely ignore it here.
    }
}

} // namespace fp::lex::detail
