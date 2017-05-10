#include <fp/util/match.h>
#include <fp/util/as_string.h>
#include <fp/lex/tokenize.h>

#include <catergorized_test.h>
#include <fp/util/console/color/support.h>
#include <fp/util/with.h>

#define TEST(what) CATEGORIZED_TEST(lex, tokenize, what)

namespace fp::lex {

template <token TOKEN>
void assert_token(const attribute_t<TOKEN>& attr, const input_view& in) {
    diagnostic_report diagnostics;
    auto tokens = tokenize(in, diagnostics);
    if (!diagnostics.errors().empty()) {
        FAIL() << diagnostics;
    }
    ASSERT_EQ(1, tokens.size());
    ASSERT_EQ(TOKEN, tokens.front().value);
    if constexpr (!std::is_same_v<no_attribute, attribute_t<TOKEN>>) {
        ASSERT_EQ(attr, tokens.front().attribute.as<TOKEN>());
    }
    ASSERT_EQ(in, tokens.front().source.symbols);
}

TEST(fiddle) {
    assert_token<token::COMMA>(no_attribute{}, "!");
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

TEST(all_tokens) {
    #include "examples/all_tokens.inl"
    assert_example(in, expected);
}

TEST(string_interpolation) {
    #include "examples/string_interpolation.inl"
    assert_example(in, expected);
}

} // namespace fp::lex
