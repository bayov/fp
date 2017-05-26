#include <boost/range/adaptor/transformed.hpp>

#include <fp/util/match.h>
#include <fp/util/as_string.h>
#include <fp/util/join.h>
#include <fp/util/console/color/support.h>
#include <fp/lex/tokenize.h>

#include <catergorized_test.h>

#define TEST(what) CATEGORIZED_TEST(lex, single_tokens, what)

namespace fp::lex {

template <token TOKEN>
void assert_token(const input_view& in) {
    diagnostic_report diagnostics;
    auto tokens = tokenize(in, diagnostics);
    if (!diagnostics.errors().empty()) {
        util::console::color::disable_in_scope disable_colors{};
        FAIL() << diagnostics;
    }
    auto& expected = util::enumerator<TOKEN>::name;
    auto actual = util::join(
        tokens | boost::adaptors::transformed([](auto&& t) {
            return util::info(t.value).name();
        })
    );
    ASSERT_EQ(expected, actual);
    ASSERT_EQ(in, tokens.begin()->source.symbols);
}

TEST(single_tokens) {
    assert_token<token::COMMA>(",");
    assert_token<token::ANNOTATION>(":");
    assert_token<token::SEMICOLON>(";");
    assert_token<token::OPTIONAL>("?");
    assert_token<token::DECORATOR>("@");
    assert_token<token::BIT_NOT>("~");
    assert_token<token::MEMBER_ACCESS>(".");
    assert_token<token::RANGE>("..");
    assert_token<token::CLOSED_RANGE>("...");

    // brackets
    assert_token<token::L_PAREN>("(");
    assert_token<token::R_PAREN>(")");
    assert_token<token::L_BRACKET>("[");
    assert_token<token::R_BRACKET>("]");
    assert_token<token::L_BRACE>("{");
    assert_token<token::R_BRACE>("}");

    // keywords
    #define FP_ASSERT_TOKEN_KEYWORD(TOKEN, in) assert_token<token::TOKEN>(in);
    FP_KEYWORDS_FOR_EACH(FP_ASSERT_TOKEN_KEYWORD)

    // arrows
    assert_token<token::TYPE_ARROW>("->");
    assert_token<token::LAMBDA_ARROW>("=>");

    // arithmetic
    assert_token<token::PLUS>("+");
    assert_token<token::MINUS>("-");
    assert_token<token::MUL>("*");
    assert_token<token::DIV>("/");
    assert_token<token::MOD>("%");
    assert_token<token::POW>("**");
    assert_token<token::BIT_AND>("&");
    assert_token<token::BIT_OR>("|");
    assert_token<token::XOR>("^");
    assert_token<token::LSHIFT>("<<");
    assert_token<token::RSHIFT>(">>");

    // assignments
    assert_token<token::ASSIGN>("=");
    assert_token<token::PLUS_ASSIGN>("+=");
    assert_token<token::MINUS_ASSIGN>("-=");
    assert_token<token::MUL_ASSIGN>("*=");
    assert_token<token::DIV_ASSIGN>("/=");
    assert_token<token::MOD_ASSIGN>("%=");
    assert_token<token::POW_ASSIGN>("**=");
    assert_token<token::BIT_AND_ASSIGN>("&=");
    assert_token<token::BIT_OR_ASSIGN>("|=");
    assert_token<token::XOR_ASSIGN>("^=");
    assert_token<token::LSHIFT_ASSIGN>("<<=");
    assert_token<token::RSHIFT_ASSIGN>(">>=");

    // comparisons
    assert_token<token::EQ>("==");
    assert_token<token::NE>("!=");
    assert_token<token::LT>("<");
    assert_token<token::GT>(">");
    assert_token<token::LTE>("<=");
    assert_token<token::GTE>(">=");

    // increment & decrement
    assert_token<token::INC>("++");
    assert_token<token::DEC>("--");
}

void assert_example(
    input_view in,
    const char* expected
) {
    diagnostic_report diagnostics;
    auto tokens = tokenize(in, diagnostics);
    std::string result;
    auto it = in.begin();
    for (auto&& t : tokens) {
        // print white-space to result (at least one space)
        if (t.source.symbols.begin() - it == 0) { result += ' '; }
        for (; it != t.source.symbols.begin(); ++it) { result += *it; }
        result += util::info(t.value).name();
        util::match(t.attribute)(
            [](const no_attribute&) {},
            [&](const auto& v) { result += "(" + util::as_string(v) + ")"; }
        );
        it = t.source.symbols.end();
    }
    for (; it != in.end(); ++it) { result += *it; }
    ASSERT_STREQ(expected, result.c_str());
}

TEST(string_interpolation) {
    #include "examples/string_interpolation.inl"
    assert_example(in, expected);
}

} // namespace fp::lex
