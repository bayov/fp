#include <gtest/gtest.h>

#include <fp/util/match.h>

namespace fp::util {

TEST(util, match) {
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
