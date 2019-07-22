#include <fp/lex/detail/characters_range.h>

#include "number.h"

namespace fp::lex::detail {

using binary_digits = characters_range<'0', '1'>;
using octal_digits  = characters_range<'0', '7'>;
using hex_digits = composite_characters_range<
    decimal_digits,
    characters_range<'A', 'F'>,
    characters_range<'a', 'f'>
>;

using decimal_exponent = composite_characters_range<
    specific_character<'e'>,
    specific_character<'E'>
>;
using hex_exponent = composite_characters_range<
    specific_character<'p'>,
    specific_character<'P'>
>;
using octal_exponent  = composite_characters_range<>;
using binary_exponent = composite_characters_range<>;

/**
 * Consumes all potentially valid characters of a number literal that appear
 * consecutively, and returns a pair `[number, exponent]` for the consumed
 * characters separated into a number and their exponent.
 *
 * `ExponentChars` specifies which characters indicate the beginning of the
 * exponent part.
 *
 * A `+` or `-` character will also be consumed (once) if it appears right after
 * the exponent character.
 *
 * This function actually consumes all valid identifier characters, so that
 * in cases such as `123z34`, only one erroneous token will be produced instead
 * of being separated into two tokens: A number `123` and identifier `z34`.
 * This makes error reporting prettier.
 */
template <class ExponentChars>
std::pair<source_view, source_view>
consume_number_characters(tokenization_state& s) {
    using number_characters = composite_characters_range<
        identifier_characters,
        specific_character<'.'>, // decimal-point
        specific_character<'\''> // digit-separator
    >;
    source_iterator number_begin = s.next;
    source_iterator exp_begin = s.end;
    for (; s.next != s.end; ++s.next) {
        if (exp_begin == s.end && ExponentChars::contain(*s.next)) {
            exp_begin = s.next;
            // consume any digit-separators
            do { ++s.next; } while (s.next_is('\''));
            // consume exponent sign
            if (s.next_is('+') || s.next_is('-')) { ++s.next; }
            // make sure we haven't reached the end
            if (s.next == s.end) { break; }
            continue;
        }
        if (number_characters::contain(*s.next)) { continue; }
        break;
    }
    if (exp_begin == s.end) { exp_begin = s.next; }
    return {
        make_source_view(number_begin, exp_begin),
        make_source_view(exp_begin, s.next)
    };
}

/**
 * Any error countered when tokenizing a number will cause a number_error to be
 * thrown. It will then be caught in detail::tokenize_number.
 *
 * Yes, this is exception-based control flow. Yes, this is not ideal. Tokenizing
 * a number is complicated business when you want nice error-reporting, so I
 * settled for throwing an exception.
 */
struct number_error : std::exception {
    source_view source_section;
    std::string text;
    number_error(source_view source_section, std::string text) :
        source_section(source_section), text(std::move(text)) {}
};

static void validate_decimal_point(source_view number, source_view exponent) {
    size_t exp_decimal_point_pos = exponent.find('.');
    if (exp_decimal_point_pos != exponent.npos) {
        throw number_error(
            number.substr(exp_decimal_point_pos, 1),
            "decimal-point in exponent"
        );
    }

    // ensure that there's no more than one decimal-point
    size_t first_pos = number.find('.');
    if (first_pos == number.npos) { return; }
    size_t second_pos = number.find('.', first_pos + 1);
    if (second_pos != number.npos) {
        throw number_error(
            number.substr(second_pos, 1),
            "more than one decimal point in number"
        );
    }
}

static void validate_no_digit_separator_next_to_exponent(
    source_view number,
    source_view exponent
) {
    if (exponent.empty()) { return; }
    source_iterator separator_adjacent_to_exp = number.end();
    if (number.back() == '\'') {
        separator_adjacent_to_exp = number.end() - 1;
    } else if (exponent[1] == '\'') {
        separator_adjacent_to_exp = exponent.begin() + 1;
    } else if (
        (exponent[1] == '+' || exponent[1] == '-') && exponent[2] == '\''
    ) {
        separator_adjacent_to_exp = exponent.begin() + 2;
    }
    if (separator_adjacent_to_exp != number.end()) {
        throw number_error(
            source_view(separator_adjacent_to_exp, 1),
            "digit-separator adjacent to exponent"
        );
    }
}

static void validate_no_consecutive_digit_separators(source_view whole_number) {
    for (auto it = whole_number.begin() + 1; it != whole_number.end(); ++it) {
        if (*it == '\'' && *(it - 1) == '\'') {
            throw number_error(
                source_view(it - 1, 2),
                "adjacent digit-separators in number"
            );
        }
    }
}

static void validate_no_digit_separator_next_to_decimal_point(
    source_view number
) {
    if (number.size() == 1) { return; }
    for (auto it = number.begin() + 1; it != number.end() - 1; ++it) {
        if (*it != '\'') { continue; }
        if (*(it - 1) == '.' || *(it + 1) == '.') {
            throw number_error(
                source_view(it, 1),
                "digit-separator adjacent to decimal-point"
            );
        }
    }
}

static void validate_digit_separators(
    source_view number,
    source_view exponent
) {
    validate_no_digit_separator_next_to_exponent(number, exponent);
    source_view whole_number = merge(number, exponent);
    validate_no_consecutive_digit_separators(whole_number);
    validate_no_digit_separator_next_to_decimal_point(number);
    if (whole_number.back() == '\'') {
        throw number_error(
            source_view(whole_number.end() - 1, 1),
            "digit-separator at the end of a number"
        );
    }
}

static void validate_exponent_digits(source_view exponent) {
    if (exponent.empty()) { return; }

    // skip exponent character
    source_view digits = exponent.substr(1);
    if (digits.empty()) {
        throw number_error(exponent, "exponent has no digits");
    }

    // skip exponent sign
    if (digits[0] == '+' || digits[0] == '-') { digits.remove_prefix(1); }

    bool has_digits = false;
    for (auto it = digits.begin(); it != digits.end(); ++it) {
        if (*it == '\'') { continue; } // skip digit-separators
        if (decimal_digits::contain(*it)) {
            has_digits = true;
        } else {
            throw number_error(
                source_view(it, 1),
                "non-decimal digit in exponent"
            );
        }
    }
    if (!has_digits) { throw number_error(exponent, "exponent has no digits"); }
}

static void validate_no_underscores(
    source_view number,
    source_view exponent
) {
    source_view whole_number = merge(number, exponent);
    size_t underscore_pos = whole_number.find('_');
    if (underscore_pos != whole_number.npos) {
        throw number_error(
            source_view(whole_number.begin() + underscore_pos, 1),
            "underscore in number"
        );
    }
}

template <class Digits>
void validate_digits(source_view number, std::string_view base_name) {
    for (auto it = number.begin(); it != number.end(); ++it) {
        if (*it == '\'' || *it == '.') { continue; }
        if (!Digits::contain(*it)) {
            throw number_error(
                source_view(it, 1),
                "non-" + std::string(base_name) + " digit in " +
                std::string(base_name) + " number"
            );
        }
    }
}

template <class Digits, class ExponentChars, bool SUPPORT_FLOAT>
void tokenize_number(tokenization_state& s, std::string_view base_name) {
    auto [number, exponent] = consume_number_characters<ExponentChars>(s);
    try {
        validate_decimal_point(number, exponent);
        validate_digit_separators(number, exponent);
        validate_exponent_digits(exponent);
        validate_no_underscores(number, exponent);
        validate_digits<Digits>(number, base_name);
    } catch (number_error& e) {
        s.report_error(e.source_section, std::move(e.text))
            .add_supplement(s.current_token_location());
        s.push_dummy(token::NUMBER);
        return;
    }

    if (!SUPPORT_FLOAT) {
        bool is_float = !exponent.empty() || number.find('.') != number.npos;
        if (is_float) {
            s.report_error(
                "floating-point literal in " + std::string(base_name) + " base "
                "is not supported"
            );
            s.push_dummy(token::NUMBER);
            return;
        }
    }

    s.push<token::NUMBER>(s.current_token_characters());
}

void tokenize_number_with_zero_prefix(tokenization_state& s) {
    if (s.next_is("0x")) {
        s.next += 2;
        tokenize_number<hex_digits, hex_exponent, true>(s, "hexadecimal");
    } else if (s.next_is("0o")) {
        s.next += 2;
        tokenize_number<octal_digits, octal_exponent, false>(s, "octal");
    } else if (s.next_is("0b")) {
        s.next += 2;
        tokenize_number<binary_digits, binary_exponent, false>(s, "binary");
    } else {
        tokenize_number<decimal_digits, decimal_exponent, true>(s, "decimal");
    }
}

void tokenize_number_with_no_zero_prefix(tokenization_state& s) {
    tokenize_number<decimal_digits, decimal_exponent, true>(s, "decimal");
}

} // namespace fp::lex::detail
