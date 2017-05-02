#include <fp/util/overloaded.h>

#include <catergorized_test.h>

#define TEST(what) CATEGORIZED_TEST(util, overloaded, what)

namespace fp::util {

TEST(basic_usage) {
    auto f = overloaded(
        [](int n) { return n + 1; },
        [](std::string s) { return "\"" + s + "\""; }
    );
    ASSERT_EQ(43, f(42));
    ASSERT_EQ(R"("hello")", f("hello"));
}

} // namespace fp::util
