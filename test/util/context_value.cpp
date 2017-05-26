#include <fp/util/with.h>
#include <fp/util/context_value.h>

#include <catergorized_test.h>

#define TEST(what) CATEGORIZED_TEST(util, context_value, what)

namespace fp::util {

TEST(basic_usage) {
    context_value<int> n;
    WITH(n(42)) {
        ASSERT_EQ(42, n.get());
        WITH(n(11)) { ASSERT_EQ(11, n.get()); }
        ASSERT_EQ(42, n.get());
    }
}

TEST(capture_by_reference) {
    context_value<int> n;
    int x = 33;
    WITH(n(x)) {
        ASSERT_EQ(33, n.get());
        x = 333;
        ASSERT_EQ(333, n.get());
    }
}

TEST(with_top_level_value_in_scope) {
    auto n = context_value<int>::with(5);
    int x = n.get();
    ASSERT_EQ(5, x);
    WITH(n(42)) { ASSERT_EQ(42, n.get()); }
}

TEST(with_top_level_reference_in_scope) {
    int x = 5;
    auto n = context_value<int>::with(x);
    ASSERT_EQ(5, n.get());
    x = 55;
    ASSERT_EQ(55, n.get());
    WITH(n(42)) { ASSERT_EQ(42, n.get()); }
}

} // namespace fp::util
