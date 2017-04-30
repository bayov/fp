#pragma once

#include <deque>

#include <fp/lex/detail/tokenizer_state.h>
#include <fp/lex/detail/tokenize_keyword_or_identifier.h>
#include <fp/lex/detail/tokenize_number.h>
#include <fp/lex/detail/tokenize_string.h>

namespace fp::lex::detail {

/// Producer of tokens from input symbols. Not thread-safe.
class tokenizer {
public:

    inline token_list tokenize(const input_view& input) {
        m_state.initialize(input);
        while (m_state.it != m_state.end) { tokenize_one(); }
        return std::move(m_state.tokens);
    }

private:

    tokenizer_state m_state;

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
    std::deque<size_t> m_string_iterpolation_stack;

    /// Tokenize a string and a terminating `"` or `{`.
    inline void tokenize_string_and_terminator() {
        tokenize_string(m_state);
        m_state.token = m_state.it;
        if (*m_state.it == '"') {
            m_state.tokenize_as<token::QUOTE>();
        } else { // *m_state.it == '{'
            m_string_iterpolation_stack.push_back(0);
            m_state.tokenize_as<token::L_BRACE>();
        }
    }

    /**
     * Tokenize the current symbol as an arithmetic `TOKEN`, or as the
     * assignment version of it (`TOKEN_ASSIGN`).
     */
    template <token TOKEN, token TOKEN_ASSIGN>
    void tokenize_arithmetic() {
        if (m_state.next_is<'='>()) {
            m_state.it += 2;
            m_state.push<TOKEN_ASSIGN>();
        } else {
            ++m_state.it;
            m_state.push<TOKEN>();
        }
    };

    inline void tokenize_one() {
        m_state.token = m_state.it;
        switch (*m_state.it) {
            case 0x00: // null (\0)
            case 0x01: // start of Heading
            case 0x02: // start of Text
            case 0x03: // end of Text
            case 0x04: // end of Transmission
            case 0x05: // enquiry
            case 0x06: // acknowledge
            case 0x07: // bell (\a)
            case 0x08: // backspace (\b)
                m_state.error();
                break;
            case 0x09: // horizontal tab (\t)
                ++m_state.it;
                break;
            case 0x0a: // line feed (\n)
                m_state.newline();
                break;
            case 0x0b: // vertical tab (\v)
            case 0x0c: // form feed (\f)
                ++m_state.it;
                break;
            case 0x0d: // carriage return (\r)
                if (m_state.next_is<'\n'>()) { ++m_state.it; } // CRLF (\r\n)
                m_state.newline();
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
                m_state.error();
                break;
            case ' ':  // 0x20
                ++m_state.it;
                break;
            case '!':  // 0x21
                if (!m_state.next_is<'='>()) {
                    m_state.error(
                        "Invalid symbol. Did you mean `not` or `!=`?"
                    );
                }
                m_state.it += 2;
                m_state.push<token::NE>();
                break;
            case '"':  // 0x22
                m_state.tokenize_as<token::QUOTE>();
                m_state.token = m_state.it;
                tokenize_string_and_terminator();
                break;
            case '#':  // 0x23
                m_state.skip_to_end_of_line();
                m_state.push<token::COMMENT>(m_state.token_symbols());
                break;
            case '$':  // 0x24
                m_state.error();
                break;
            case '%':  // 0x25
                tokenize_arithmetic<token::MOD, token::MOD_ASSIGN>();
                break;
            case '&':  // 0x26
                tokenize_arithmetic<token::BIT_AND, token::BIT_AND_ASSIGN>();
                break;
            case '\'': // 0x27
                tokenize_char(m_state);
                break;
            case '(':  // 0x28
                m_state.tokenize_as<token::L_PAREN>();
                break;
            case ')':  // 0x29
                m_state.tokenize_as<token::R_PAREN>();
                break;
            case '*':  // 0x2a
                if (m_state.next_is<'='>()) {
                    ++m_state.it;
                    m_state.tokenize_as<token::MUL_ASSIGN>();
                } else if (m_state.next_is<'*'>()) {
                    ++m_state.it;
                    tokenize_arithmetic<token::POW, token::POW_ASSIGN>();
                } else {
                    m_state.tokenize_as<token::MUL>();
                }
                break;
            case '+':  // 0x2b
                if (m_state.next_is<'+'>()) {
                    ++m_state.it;
                    m_state.tokenize_as<token::INC>();
                } else {
                    tokenize_arithmetic<token::PLUS, token::PLUS_ASSIGN>();
                }
                break;
            case ',':  // 0x2c
                m_state.tokenize_as<token::COMMA>();
                break;
            case '-':  // 0x2d
                if (m_state.next_is<'-'>()) {
                    ++m_state.it;
                    m_state.tokenize_as<token::DEC>();
                } else {
                    tokenize_arithmetic<token::MINUS, token::MINUS_ASSIGN>();
                }
                break;
            case '.':  // 0x2e
                if (m_state.next_is<'.'>()) {
                    ++m_state.it;
                    if (m_state.next_is<'.'>()) {
                        ++m_state.it;
                        m_state.tokenize_as<token::CLOSED_RANGE>();
                    } else {
                        m_state.tokenize_as<token::RANGE>();
                    }
                } else {
                    m_state.tokenize_as<token::PERIOD>();
                }
                break;
            case '/':  // 0x2f
                tokenize_arithmetic<token::DIV, token::DIV_ASSIGN>();
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
                tokenize_number(m_state);
                break;
            case ':':  // 0x3a
                m_state.tokenize_as<token::COLON>();
                break;
            case ';':  // 0x3b
                m_state.tokenize_as<token::SEMICOLON>();
                break;
            case '<':  // 0x3c
                if (m_state.next_is<'='>()) {
                    ++m_state.it;
                    m_state.tokenize_as<token::LTE>();
                } else if (m_state.next_is<'<'>()) {
                    ++m_state.it;
                    tokenize_arithmetic<token::LSHIFT, token::LSHIFT_ASSIGN>();
                } else {
                    m_state.tokenize_as<token::LT>();
                }
                break;
            case '=':  // 0x3d
                if (m_state.next_is<'='>()) {
                    ++m_state.it;
                    m_state.tokenize_as<token::EQ>();
                } else if (m_state.next_is<'>'>()) {
                    ++m_state.it;
                    m_state.tokenize_as<token::LAMBDA_ARROW>();
                } else {
                    m_state.tokenize_as<token::ASSIGN>();
                }
                break;
            case '>':  // 0x3e
                if (m_state.next_is<'='>()) {
                    ++m_state.it;
                    m_state.tokenize_as<token::GTE>();
                } else if (m_state.next_is<'>'>()) {
                    ++m_state.it;
                    tokenize_arithmetic<token::RSHIFT, token::RSHIFT_ASSIGN>();
                } else {
                    m_state.tokenize_as<token::GT>();
                }
                break;
            case '?':  // 0x3f
                m_state.tokenize_as<token::OPTIONAL>();
                break;
            case '@':  // 0x40
                m_state.tokenize_as<token::DECORATOR>();
                break;
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
                tokenize_identifier(m_state);
                break;
            case '[':  // 0x5b
                m_state.tokenize_as<token::L_BRACKET>();
                break;
            case '\\': // 0x5c
                m_state.error();
                break;
            case ']':  // 0x5d
                m_state.tokenize_as<token::R_BRACKET>();
                break;
            case '^':  // 0x5e
                tokenize_arithmetic<token::XOR, token::XOR_ASSIGN>();
                break;
            case '_':  // 0x5f
                tokenize_identifier(m_state);
                break;
            case '`':  // 0x60
                m_state.error();
                break;
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
                tokenize_keyword_or_identifier(m_state);
                break;
            case '{':  // 0x7b
                m_state.tokenize_as<token::L_BRACE>();
                if (!m_string_iterpolation_stack.empty()) {
                    ++m_string_iterpolation_stack.back();
                }
                break;
            case '|':  // 0x7c
                tokenize_arithmetic<token::BIT_OR, token::BIT_OR_ASSIGN>();
                break;
            case '}':  // 0x7d
                m_state.tokenize_as<token::R_BRACE>();
                m_state.token = m_state.it;
                if (!m_string_iterpolation_stack.empty()) {
                    if (m_string_iterpolation_stack.back() == 0) {
                        m_string_iterpolation_stack.pop_back();
                        tokenize_string_and_terminator();
                    } else {
                        --m_string_iterpolation_stack.back();
                    }
                }
                break;
            case '~':  // 0x7e
                m_state.tokenize_as<token::BIT_NOT>();
                break;
            case 0x7f: // delete
            default:
                m_state.error();
        }
    }

};

} // fp::lex::detail
