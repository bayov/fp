#include <sstream>

#include <gtest/gtest.h>

#include <fp/util/with.h>
#include <fp/util/context_value.h>

namespace fp::util {

TEST(context_value, basic_usage) {
    context_value<int> n(42);
    ASSERT_EQ(42, n.get());
    FP_WITH(n = 11) {
        ASSERT_EQ(11, n.get());
        FP_WITH(n = 5) { ASSERT_EQ(5, n.get()); }
        ASSERT_EQ(11, n.get());
    }
    ASSERT_EQ(42, n.get());
}

TEST(context_value, scope_can_refer_to_a_reference) {
    context_value<int> n(42);
    int refer_to_me = 11;
    FP_WITH(n = refer_to_me) {
        ASSERT_EQ(11, n.get());
        refer_to_me = 3;
        ASSERT_EQ(3, n.get());
    }
    ASSERT_EQ(42, n.get());
}

TEST(context_value, can_store_a_base_type) {
    context_value<std::ostream> logger;

    std::ostringstream oss1;
    std::ostringstream oss2;

    FP_WITH(logger = oss1) { logger.get() << "hello"; }
    FP_WITH(logger = oss2) { logger.get() << "world"; }

    ASSERT_EQ("hello", oss1.str());
    ASSERT_EQ("world", oss2.str());
}

TEST(context_value, is_iterable) {
    context_value<int> n;
    auto expect_items_equal_to = [&](std::vector<int> expected) {
        EXPECT_EQ(expected, std::vector<int>(n.begin(), n.end()));
    };
    FP_WITH(n = 42) {
        FP_WITH(n = 11) {
            FP_WITH(n = 5) { expect_items_equal_to({ 42, 11, 5 }); }
            expect_items_equal_to({ 42, 11 });
        }
        expect_items_equal_to({ 42 });
    }
    expect_items_equal_to({ });
}

} // namespace fp::util
