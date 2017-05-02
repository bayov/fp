#include <fp/util/match.h>
#include <fp/util/as_string.h>
#include <fp/lex/tokenize.h>

#include <catergorized_test.h>

#define TEST(what) CATEGORIZED_TEST(lex, tokenize, what)

namespace fp::lex {

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
