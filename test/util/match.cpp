#include <fp/util/match.h>

#include <catergorized_test.h>

#define TEST(what) CATEGORIZED_TEST(util, match, what)

namespace fp::util {

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

} // fp::util
