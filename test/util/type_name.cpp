#include <gtest/gtest.h>

#include <fp/util/type_name.h>

namespace fp::util {

template <class T> struct foo {};

TEST(util, type_name) {
    ASSERT_EQ("int", type_name<int>);
    ASSERT_EQ("fp::util::foo<int>", type_name<foo<int>>);
}

} // namespace fp::util
