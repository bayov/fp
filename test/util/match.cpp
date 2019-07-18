#include <fp/util/match.h>

#include <test-util/catergorized_test.h>

namespace fp::util {

#define TEST(what) CATEGORIZED_TEST(util, match, what)

TEST(basic_usage) {
    std::variant<int, std::string> w("hello");
    auto s = match(w)(
        [](int) { return "int"; },
        [](std::string) { return "string"; }
    );
    ASSERT_EQ("string", s);

    w = 42;
    s = match(w)(
        [](int) { return "int"; },
        [](std::string) { return "string"; }
    );
    ASSERT_EQ("int", s);
}

} // namespace fp::util
