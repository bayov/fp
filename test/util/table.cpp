#include <fp/util/table.h>

#include <catergorized_test.h>

#define TEST(what) CATEGORIZED_TEST(util, table, what)

namespace fp::util {

using handler_t = int (*)(int);

int as_is(int n) { return n; }
int plus_one(int n) { return n + 1; }
int times_two(int n) { return 2 * n; }

constexpr auto handler_table = ([]() {
    auto t = table<char, handler_t, 100>::with_default(as_is);
    t['1'] = plus_one;
    t['*'] = times_two;
    return t;
})();

TEST(basic_usage) {
    ASSERT_EQ(42, handler_table['c'](42));
    ASSERT_EQ(43, handler_table['1'](42));
    ASSERT_EQ(84, handler_table['*'](42));
}

} // namespace fp::util
