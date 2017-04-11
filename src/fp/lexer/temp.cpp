#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <limits>

namespace fp {

enum class token : uint8_t;
using token_underlying_type = std::underlying_type_t<token>;

enum class token : uint8_t {
    // The following tokens must have a value equal to their respective ASCII
    // number, since they will be reinterpret-casted directly from an input
    // character.
    // ---------------------------------------------------------------------
    QUOTE = 0x22,       ///< "
    COMMENT = 0x23,     ///< # some comment...
    COMMA = 0x2c,       ///< ,
    COLON = 0x3a,       ///< :
    SEMICOLON = 0x3b,   ///< ;
    OPTIONAL = 0x3f,    ///< ?
    DECORATOR = 0x40,   ///< @
    BIT_NOT = 0x7e,     ///< ~

    // brackets
    L_PAREN = 0x28,     ///< (
    R_PAREN = 0x29,     ///< )
    L_BRACKET = 0x5b,   ///< [
    R_BRACKET = 0x5d,   ///< ]
    L_BRACE = 0x7b,     ///< {
    R_BRACE = 0x7d,     ///< }

    // The following tokens are not reinterpret-casted, and should be any
    // non-ASCII value (beginning from 0x80).
    // ---------------------------------------------------------------------
    PERIOD = 0x80,      ///< .
    RANGE,              ///< ..
    CRANGE,             ///< ...

    // keywords
    AND,                ///< and
    AS,                 ///< as
    BREAK,              ///< break
    CASE,               ///< case
    CATCH,              ///< catch
    CLASS,              ///< class
    CONCEPT,            ///< concept
    CONTINUE,           ///< continue
    DEFAULT,            ///< default
    DO,                 ///< do
    ELSE,               ///< else
    ENUM,               ///< enum
    EXPORT,             ///< export
    FOR,                ///< for
    IF,                 ///< if
    IMPLICIT,           ///< implicit
    IMPORT,             ///< import
    IN,                 ///< in
    MUT,                ///< mut
    NOT,                ///< not
    OF,                 ///< of
    OR,                 ///< or
    OVERRIDE,           ///< override
    RETURN,             ///< return
    SELF,               ///< self
    SWITCH,             ///< switch
    THROW,              ///< throw
    TRY,                ///< try
    WHILE,              ///< while

    // functions
    TYPE_ARROW,         ///< ->
    LAMBDA_ARROW,       ///< =>

    // arithmetic
    PLUS,               ///< +
    MINUS,              ///< -
    MUL,                ///< *
    DIV,                ///< /
    MOD,                ///< %
    POW,                ///< **
    BIT_AND,            ///< &
    BIT_OR,             ///< |
    XOR,                ///< ^
    LSHIFT,             ///< <<
    RSHIFT,             ///< >>

    // assignment
    ASSIGN,             ///< =
    PLUS_ASSIGN,        ///< +=
    MINUS_ASSIGN,       ///< -=
    MUL_ASSIGN,         ///< *=
    DIV_ASSIGN,         ///< /=
    MOD_ASSIGN,         ///< %=
    POW_ASSIGN,         ///< **=
    BIT_AND_ASSIGN,     ///< &=
    BIT_OR_ASSIGN,      ///< |=
    XOR_ASSIGN,         ///< ^=
    LSHIFT_ASSIGN,      ///< <<=
    RSHIFT_ASSIGN,      ///< >>=

    // comparison
    EQ,                 ///< ==
    NE,                 ///< !=
    LT,                 ///< <
    GT,                 ///< >
    LTE,                ///< <=
    GTE,                ///< >=

    // increment & decrement
    INC,                ///< ++
    DEC,                ///< --

    // containing attributes
    IDENTIFIER,         ///< some_identifier, Can_Be_CAPITALIZED
    NUMBER,             ///< 42, 0xFF, 0b11, 1`000`000, etc.
    CHAR,               ///< 'a'

    /**
     * String tokens are handled a bit differently.
     *
     * The lexer will tokenize `"Hello, World\n"` as `QUOTE STRING QUOTE`. But,
     * as we need to support string-interpolation (embedded expressions inside
     * strings), the following:
     *      "one plus one is {1 + 1}."
     *
     * will be tokenized as:
     *      QUOTE STRING L_BRACE NUMBER PLUS NUMBER R_BRACE STRING QUOTE
     *            ^                                         ^
     *            "one plus one is "                        "."
     */
    STRING,

    // The following tokens are only aliases to existing tokens, because these
    // tokens have an overloaded meaning.
    // ---------------------------------------------------------------------
    REF = token_underlying_type(BIT_AND),
    L_GENERIC_BRACKET = token_underlying_type(LT),
    R_GENERIC_BRACKET = token_underlying_type(GT)

    // IMPORTANT: don't define any new tokens past this point, since the
    // above alias section has messed the enumerator numbering.
};

class lexer_error : public std::logic_error {
public:

    explicit lexer_error(std::string what) : logic_error(std::move(what)) {}

};

class invalid_symbol : public lexer_error {
public:

    explicit invalid_symbol(char symbol) :
        invalid_symbol(std::string(1, symbol))
    {}

    explicit invalid_symbol(std::string symbol) :
        // TODO: pretty print symbol
        lexer_error("Invalid symbol: " + std::move(symbol))
    {}

};

class token_list {
public:

    const std::vector<token>& tokens() const { return m_tokens; }

    void push(token t) {
        m_tokens.push_back(t);
        m_attributes.push_back(no_attribute{});
    }

    void push(token t, std::string s) {
        m_tokens.push_back(t);
        m_attributes.push_back(std::move(s));
    }

    const std::string& comment(size_t pos) const {
        return boost::get<std::string>(m_attributes[pos]);
    }

private:

    struct no_attribute {};
    using attribute = boost::variant<no_attribute, std::string>;

    std::vector<token> m_tokens;
    std::vector<attribute> m_attributes;

};

// not thread-safe
template <class SymbolRange = std::string>
class lexer {
public:

    using symbol_range = SymbolRange;
    using symbol_type = typename symbol_range::value_type;

    static_assert(
        std::is_same<symbol_type, char>::value,
        "SymbolRange must hold values of type `char`"
    );

    explicit lexer(const symbol_range& r) : m_it(r.begin()), m_end(r.end()) {}

    const token_list& tokenize() {
        while (m_it != m_end) { tokenize_one(); }
        return m_tokens;
    }

private:

    using symbol_iterator = typename symbol_range::const_iterator;

    token_list m_tokens;
    symbol_iterator m_it;
    symbol_iterator m_end;

    void invalid() { throw invalid_symbol(*m_it); }

    void skip(size_t n) { m_it += n; }

    void skip() { ++m_it; }

    template <class... Args>
    void push(token t, Args&&... args) {
        m_tokens.push(t, std::forward<Args>(args)...);
    }

    template <size_t INCREMENT = 1>
    bool following(char symbol) {
        return m_it + INCREMENT != m_end && *(m_it + INCREMENT) == symbol;
    }

    template <size_t INCREMENT = 1, class... Symbols>
    bool following(char symbol1, char symbol2, Symbols... symbols) {
        return following<INCREMENT>(symbol1) &&
               following<INCREMENT + 1>(symbol2, symbols...);
    }

    template <class... Symbols>
    void consume_following(token t, Symbols... symbols) {
        if (!following(symbols...)) { invalid(); }
        skip(1 + sizeof...(symbols));
        push(t);
    }

    void consume_as(token t) {
        push(t);
        skip();
    }

    void consume_as(size_t n, token t) {
        push(t);
        skip(n);
    }

    void consume_as_is() { consume_as(token(*m_it)); }

    void consume_comment() {
        skip();
        auto comment_start = m_it;
        while (m_it != m_end && *m_it != '\n' && *m_it != '\r') { skip(); }
        push(token::COMMENT, std::string(comment_start, m_it));
    }

    void consume_char() {
        skip();
        auto char_start = m_it;
        while (m_it != m_end && *m_it != '\'') { skip(); }
        push(token::COMMENT, std::string(comment_start, m_it));
    }

    void tokenize_one() {
        #define CONSUME_ARITHMETIC_OR_ASSIGNMENT(sign, token_name)\
                if (following(sign)) {\
                    consume_as(2, token::token_name##_ASSIGN);\
                } else {\
                    consume_as(token::token_name);\
                }
        switch (*m_it) {
            case 0x00: // null (\0)
            case 0x01: // start of Heading
            case 0x02: // start of Text
            case 0x03: // end of Text
            case 0x04: // end of Transmission
            case 0x05: // enquiry
            case 0x06: // acknowledge
            case 0x07: // bell (\a)
            case 0x08: // backspace (\b)
                invalid();
                break;
            case 0x09: // horizontal tab (\t)
            case 0x0a: // line feed (\n)
            case 0x0b: // vertical tab (\v)
            case 0x0c: // form feed (\f)
            case 0x0d: // carriage return (\r)
                skip();
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
                invalid();
                break;
            case ' ':  // 0x20
                skip();
                break;
            case '!':  // 0x21
                consume_following(token::NE, '=');
                break;
            case '"':  // 0x22
                consume_as_is();
                break;
            case '#':  // 0x23
                consume_comment();
                break;
            case '$':  // 0x24
                invalid();
                break;
            case '%':  // 0x25
                CONSUME_ARITHMETIC_OR_ASSIGNMENT('=', MOD);
                break;
            case '&':  // 0x26
                CONSUME_ARITHMETIC_OR_ASSIGNMENT('&', BIT_AND);
                break;
            case '\'': // 0x27
            case '(':  // 0x28
            case ')':  // 0x29
            case '*':  // 0x2a
            case '+':  // 0x2b
            case ',':  // 0x2c
            case '-':  // 0x2d
            case '.':  // 0x2e
            case '/':  // 0x2f
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
                invalid();
        }
    }

};

}

int main() {
    try {
        std::string symbols = "  \" \t\n  \r !=\" # comment! = \t\"\r!= \v  !=\f";
        fp::lexer<> lexer(symbols);
        auto tokens = lexer.tokenize();
        std::vector<fp::token> expected = {
            fp::token::QUOTE,
            fp::token::NE,
            fp::token::QUOTE,
            fp::token::COMMENT,
            fp::token::NE,
            fp::token::NE
        };

        std::cout << (tokens.tokens() == expected) << std::endl;
        std::cout << '#' << tokens.comment(3) << std::endl;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
