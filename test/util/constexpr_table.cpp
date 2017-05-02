#include <fp/util/constexpr_table.h>

#include <catergorized_test.h>

#define TEST(what) CATEGORIZED_TEST(util, constexpr_table, what)

namespace fp::util {

using handler_t = int (*)(int);

int as_is(int n) { return n; }
int plus_one(int n) { return n + 1; }
int times_two(int n) { return 2 * n; }

using my_table = constexpr_table<char, handler_t, 100>
    ::set_default<as_is>
    ::set<'1', plus_one>
    ::set<'*', times_two>;

TEST(basic_usage) {
    ASSERT_EQ(42, my_table::get('c')(42));
    ASSERT_EQ(43, my_table::get('1')(42));
    ASSERT_EQ(84, my_table::get('*')(42));
}

} // namespace fp::util
