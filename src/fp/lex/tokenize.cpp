#include <cstdlib>

#include "tokenize.h"

namespace fp::lex {

namespace detail {

/// A compile-time range of symbols.
template <symbol_t FROM, symbol_t TO>
struct symbol_range {

    /// @return `true` if the given symbol is inside the range.
    static bool contain(symbol_t s) { return FROM <= s && s <= TO; }

    static std::string as_string() { return FROM + std::string("-") + TO; }

};

/// Contains multiple compile-time symbol ranges (@ref symbol_range).
template <class... SymbolRanges>
struct composite_symbol_range {

    /// @return `true` if the given symbol is contained in one of the ranges.
    static bool contain(symbol_t s) {
        return (... || SymbolRanges::contain(s));
    }

    static std::string as_string() {
        auto result = (... + (SymbolRanges::as_string() + ' '));
        result.pop_back();
        return result;
    }

};

/// Contains all valid symbols of identifiers in the language.
using identifier_symbols = composite_symbol_range<
    symbol_range<'_', '_'>,
    symbol_range<'a', 'z'>,
    symbol_range<'A', 'Z'>,
    symbol_range<'0', '9'>
>;

/// Error message that is reported when expecting a digit. Takes a symbol range.
#define DIGIT_ERROR_MESSAGE(digits) "Expected a digit: " + digits::as_string()

/// Producer of tokens from input symbols. Not thread-safe.
class tokenizer {
public:

    token_list tokenize(const input_view_t& input) {
        m_tokens = token_list();
        m_it = input.begin();
        m_end = input.end();
        m_line = m_it;
        m_line_number = 1;
        while (m_it != m_end) { tokenize_one(); }
        return std::move(m_tokens);
    }

private:

    token_list m_tokens;    ///< The current token list.
    symbol_iterator m_it;   ///< The current symbol.
    symbol_iterator m_end;  ///< The last symbol of the input.
    symbol_iterator m_line; ///< The beginning of the current line.
    size_t m_line_number;   ///< The current line number.

    /// The beginning symbol of the current token being parsed.
    symbol_iterator m_token_begin;

    /// Throw an error with the symbols of the current token being parsed.
    void throw_error(std::string what = "Invalid symbol") const {
        throw_error(m_token_begin, m_it + 1, std::move(what));
    }

    /// Throw an error with the symbols `[from, to)`.
    void throw_error(
        symbol_iterator from,
        symbol_iterator to,
        std::string what = "Invalid symbol"
    ) const {
        throw error(
            input_view_t(from, to),
            m_line,
            m_line_number,
            std::move(what)
        );
    }

    /// Parse the current symbol as a new-line.
    void newline() {
        ++m_it;
        m_line = m_it;
        ++m_line_number;
    }

    /**
     * `is<S_1, S_2, ..., S_k>` is `true` if the current symbol is `S_1`,
     * followed immediately by `S2`, ..., `S_k`.
     */
    template <symbol_t... SYMBOLS, size_t... INDICES>
    bool next_is_impl(std::index_sequence<INDICES...>) const {
        if (m_it + sizeof...(SYMBOLS) >= m_end) { return false; }
        return (... && (*(m_it + 1 + INDICES) == SYMBOLS));
    }

    template <symbol_t... SYMBOLS>
    bool next_is() const {
        using INDICES = std::make_index_sequence<sizeof...(SYMBOLS)>;
        return next_is_impl<SYMBOLS...>(INDICES{});
    }

    /// Implementation detail: End of recursion.
    //template <size_t N> bool next_is() const { return true; }

    /// Push a new token to the list, with `args` forwarded to its attribute.
    template <token TOKEN, class... Args>
    void push(Args&&... args) {
        m_tokens.push_back<TOKEN>(
            token_source(
                input_view_t(m_token_begin, m_it),
                m_line,
                m_line_number
            ),
            attribute<TOKEN>(std::forward<Args>(args)...)
        );
    }

    /// Consume the current symbol as `TOKEN`.
    template <token TOKEN>
    void consume_as() {
        ++m_it;
        push<TOKEN>();
    }

    /// Skip to the next `'\n'` or `'\r'`.
    void skip_to_end_of_line() {
        while (m_it != m_end && *m_it != '\n' && *m_it != '\r') { ++m_it; }
    }

    /**
     * Consume the current symbol as an arithmetic `TOKEN`, or as the assignment
     * version of it (`TOKEN_ASSIGN`).
     */
    template <token TOKEN, token TOKEN_ASSIGN>
    void consume_arithmetic() {
        if (next_is<'='>()) {
            m_it += 2;
            push<TOKEN_ASSIGN>();
        } else {
            ++m_it;
            push<TOKEN>();
        }
    };

    template <class Digits, class ParseDigit>
    void consume_number_literal(ParseDigit parse_digit) {
        integer_type value = 0;
        bool expecting_digit = true;
        bool overflow = false;
        for (; m_it != m_end; ++m_it) {
            if (expecting_digit && !Digits::contain(*m_it)) {
                throw_error(m_it, m_it, DIGIT_ERROR_MESSAGE(Digits));
            }
            if (*m_it == '`') {
                expecting_digit = true;
                continue;
            }
            if (!Digits::contain(*m_it)) {
                if (identifier_symbols::contain(*m_it)) {
                    throw_error(m_it, m_it + 1, DIGIT_ERROR_MESSAGE(Digits));
                }
                if (overflow) {
                    throw_error("Literal number is too big (will overflow)");
                }
                push<token::INTEGER>(value);
                return;
            }
            auto previous_value = value;
            parse_digit(*m_it, value);
            if (value < previous_value) { overflow = true; }
            expecting_digit = false;
        }
        if (expecting_digit) {
            throw_error(m_it, m_it, DIGIT_ERROR_MESSAGE(Digits));
        }
    }

    void consume_hex_literal() {
        m_it += 2; // skip over `0x` prefix
        using digits = composite_symbol_range<
            symbol_range<'0', '9'>,
            symbol_range<'a', 'f'>,
            symbol_range<'A', 'F'>
        >;
        consume_number_literal<digits>([](symbol_t s, integer_type& v) {
            integer_type d;
            if (s <= '9') {
                d = integer_type(s - '0');          // 0-9
            } else if (s >= 'a') {
                d = integer_type(s - 'a') + 10;     // a-f
            } else {
                d = integer_type(s - 'A') + 10;     // A-F
            }
            v = (v << 4) | d;
        });
    }

    void consume_octal_literal() {
        m_it += 2; // skip over `0o` prefix
        using digits = symbol_range<'0', '7'>;
        consume_number_literal<digits>([](symbol_t s, integer_type& v) {
            v = (v << 3) | (s - '0');
        });
    }

    void consume_binary_literal() {
        m_it += 2; // skip over `0b` prefix
        using digits = symbol_range<'0', '1'>;
        consume_number_literal<digits>([](symbol_t s, integer_type& v) {
            v = (v << 1) | (s - '0');
        });
    }

    void consume_decimal_literal() {
        using digits = symbol_range<'0', '9'>;
        consume_number_literal<digits>([](symbol_t s, integer_type& v) {
            v = (v * 10) + (s - '0');
        });
    }

    /**
     * Consume the upcoming symbols as a floating-type literal (token::FLOAT).
     *
     * @todo Parse manually, instead of using std::strtod. (not easy...)
     */
    void consume_floating_literal() {
        using digits = symbol_range<'0', '9'>;

        // first, ensure that the floating literal is well-formed.
        bool decimal_mark_seen = false;
        bool exponent_seen = false;
        auto it = m_it + 1; // we already know that the first number is a digit
        for (; it != m_end; ++it) {
            if (*it == '`') {
                throw_error(
                    it, it + 1,
                    "Currently, ` marks inside floating-point literals are not "
                    "supported. This feature will be added in the future."
                );
            }
            if (*it == '.') {
                if (decimal_mark_seen) {
                    throw_error(it, it + 1, "Second decimal mark");
                }
                decimal_mark_seen = true;
                continue;
            }
            if (*it == 'e' || *it == 'E') {
                if (exponent_seen) {
                    throw_error(it, it + 1, "Encountered a second exponent");
                }
                exponent_seen = true;
                if (*it == '+' || *it == '-') { // allow sign after exponent
                    ++it;
                    if (it == m_end || !digits::contain(*it)) {
                        throw_error(it, it, DIGIT_ERROR_MESSAGE(digits));
                    }
                }
                continue;
            }
            if (!digits::contain(*it)) {
                if (identifier_symbols::contain(*it)) {
                    throw_error(it, it + 1, DIGIT_ERROR_MESSAGE(digits));
                }
                break;
            }
        }

        // From this point, we know that `[m_it, it)` is a well-formed float

        // since we are using std::strtod, we cannot control when it stops
        // parsing if the floating-point literal is at the end of the input.
        // We can't assume that the input string ends with '\0', so for now we
        // must throw an error here.
        if (it == m_end) {
            throw_error(
                "Real literals at the end of the input are not yet supported.\n"
                "This is a technical issue that will be solved in the future."
            );
        }

        float_type value = std::strtod(&*m_it, nullptr);
        if (errno == ERANGE) {
            errno = 0;
            if (value == 0) {
                throw_error(
                    "Literal number is too small (will be truncated to zero).\n"
                );
            } else {
                throw_error(
                    "Literal number is too big (will overflow).\n"
                );
            }
        }

        push<token::FLOAT>(value);
    }

    void consume_decimal_or_floating() {
        using decimal_symbols = composite_symbol_range<
            symbol_range<'0', '9'>,
            symbol_range<'`', '`'>
        >;

        // skip to first non-decimal symbol
        auto it = m_it + 1; // we already know that the first number is a digit
        while (it != m_end && decimal_symbols::contain(*it)) { ++it; }

        if (it != m_end && (*it == '.' || *it == 'e' || *it == 'E')) {
            consume_floating_literal();
        } else {
            consume_decimal_literal();
        }
    }

    void consume_number() {
        if (*m_it != '0' || m_it + 1 == m_end) {
            consume_decimal_or_floating();
            return;
        }
        switch (*(m_it + 1)) {
            case 'x':
                consume_hex_literal();
                break;
            case 'o':
                consume_octal_literal();
                break;
            case 'b':
                consume_binary_literal();
                break;
            default:
                consume_decimal_or_floating();
                break;
        }
    };

    void tokenize_one() {
        m_token_begin = m_it;
        switch (*m_token_begin) {
            case 0x00: // null (\0)
            case 0x01: // start of Heading
            case 0x02: // start of Text
            case 0x03: // end of Text
            case 0x04: // end of Transmission
            case 0x05: // enquiry
            case 0x06: // acknowledge
            case 0x07: // bell (\a)
            case 0x08: // backspace (\b)
                throw_error();
                break;
            case 0x09: // horizontal tab (\t)
                ++m_it;
                break;
            case 0x0a: // line feed (\n)
                newline();
                break;
            case 0x0b: // vertical tab (\v)
            case 0x0c: // form feed (\f)
                ++m_it;
                break;
            case 0x0d: // carriage return (\r)
                if (next_is<'\n'>()) { ++m_it; } // CRLF (\r\n)
                newline();
                break;
            case 0x0e: // shift out
            case 0x0f: // shift in
            case 0x10: // data link escape
            case 0x11: // device control 1
            case 0x12: // device control 2
            case 0x13: // device control 3
            case 0x14: // device control 4
            case 0x15: // negative acknowledge
            case 0x16: // synchronous idle
            case 0x17: // end of transmission block
            case 0x18: // cancel
            case 0x19: // end of medium
            case 0x1a: // substitute
            case 0x1b: // escape (\e)
            case 0x1c: // file separator
            case 0x1d: // group separator
            case 0x1e: // record separator
            case 0x1f: // unit separator
                throw_error();
                break;
            case ' ':  // 0x20
                ++m_it;
                break;
            case '!':  // 0x21
                if (!next_is<'='>()) {
                    throw_error("Invalid symbol. Did you mean `not` or `!=`?");
                }
                m_it += 2;
                push<token::NE>();
                break;
            case '"':  // 0x22
                consume_as<token::QUOTE>();
                break;
            case '#':  // 0x23
                skip_to_end_of_line();
                push<token::COMMENT>(input_view_t(m_token_begin, m_it));
                break;
            case '$':  // 0x24
                throw_error();
                break;
            case '%':  // 0x25
                consume_arithmetic<token::MOD, token::MOD_ASSIGN>();
                break;
            case '&':  // 0x26
                consume_arithmetic<token::BIT_AND, token::BIT_AND_ASSIGN>();
                break;
            case '\'': // 0x27
                throw_error();
                break;
            case '(':  // 0x28
                consume_as<token::L_PAREN>();
                break;
            case ')':  // 0x29
                consume_as<token::R_PAREN>();
                break;
            case '*':  // 0x2a
                consume_arithmetic<token::MUL, token::MUL_ASSIGN>();
                break;
            case '+':  // 0x2b
                consume_arithmetic<token::PLUS, token::PLUS_ASSIGN>();
                break;
            case ',':  // 0x2c
                consume_as<token::COMMA>();
                break;
            case '-':  // 0x2d
                consume_arithmetic<token::MINUS, token::MINUS_ASSIGN>();
                break;
            case '.':  // 0x2e
                if (next_is<'.'>()) {
                    ++m_it;
                    if (next_is<'.'>()) {
                        ++m_it;
                        consume_as<token::CLOSED_RANGE>();
                    } else {
                        consume_as<token::RANGE>();
                    }
                } else {
                    consume_as<token::PERIOD>();
                }
                break;
            case '/':  // 0x2f
                consume_arithmetic<token::DIV, token::DIV_ASSIGN>();
                break;
            case '0':  // 0x30
            case '1':  // 0x31
            case '2':  // 0x32
            case '3':  // 0x33
            case '4':  // 0x34
            case '5':  // 0x35
            case '6':  // 0x36
            case '7':  // 0x37
            case '8':  // 0x38
            case '9':  // 0x39
                consume_number();
                break;
            case ':':  // 0x3a
            case ';':  // 0x3b
            case '<':  // 0x3c
            case '=':  // 0x3d
            case '>':  // 0x3e
            case '?':  // 0x3f
            case '@':  // 0x40
            case 'A':  // 0x41
            case 'B':  // 0x42
            case 'C':  // 0x43
            case 'D':  // 0x44
            case 'E':  // 0x45
            case 'F':  // 0x46
            case 'G':  // 0x47
            case 'H':  // 0x48
            case 'I':  // 0x49
            case 'J':  // 0x4a
            case 'K':  // 0x4b
            case 'L':  // 0x4c
            case 'M':  // 0x4d
            case 'N':  // 0x4e
            case 'O':  // 0x4f
            case 'P':  // 0x50
            case 'Q':  // 0x51
            case 'R':  // 0x52
            case 'S':  // 0x53
            case 'T':  // 0x54
            case 'U':  // 0x55
            case 'V':  // 0x56
            case 'W':  // 0x57
            case 'X':  // 0x58
            case 'Y':  // 0x59
            case 'Z':  // 0x5a
            case '[':  // 0x5b
            case '\\': // 0x5c
            case ']':  // 0x5d
            case '^':  // 0x5e
            case '_':  // 0x5f
            case '`':  // 0x60
            case 'a':  // 0x61
            case 'b':  // 0x62
            case 'c':  // 0x63
            case 'd':  // 0x64
            case 'e':  // 0x65
            case 'f':  // 0x66
            case 'g':  // 0x67
            case 'h':  // 0x68
            case 'i':  // 0x69
            case 'j':  // 0x6a
            case 'k':  // 0x6b
            case 'l':  // 0x6c
            case 'm':  // 0x6d
            case 'n':  // 0x6e
            case 'o':  // 0x6f
            case 'p':  // 0x70
            case 'q':  // 0x71
            case 'r':  // 0x72
            case 's':  // 0x73
            case 't':  // 0x74
            case 'u':  // 0x75
            case 'v':  // 0x76
            case 'w':  // 0x77
            case 'x':  // 0x78
            case 'y':  // 0x79
            case 'z':  // 0x7a
            case '{':  // 0x7b
            case '|':  // 0x7c
            case '}':  // 0x7d
            case '~':  // 0x7e
            case 0x7f: // delete
            default:
                throw_error();
        }
    }

};

} // detail

token_list tokenize(const input_t& input) {
    return detail::tokenizer().tokenize(make_input_view(input));
}

token_list tokenize(const input_view_t& input) {
    return detail::tokenizer().tokenize(input);
}


} // fp::lex
