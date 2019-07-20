#include <gtest/gtest.h>

#include <fp/util/type_name.h>

namespace fp::util {

template <class T> struct foo {};

TEST(util, type_name) {
    ASSERT_EQ("int", type_name(42));
    ASSERT_EQ("int", type_name<int>());

    // template
    ASSERT_EQ("fp::util::foo<int>", type_name<foo<int>>());

    ASSERT_EQ("int&"       , qualified_type_name<int&       >());
    ASSERT_EQ("int&&"      , qualified_type_name<int&&      >());
    ASSERT_EQ("int const"  , qualified_type_name<const int  >());
    ASSERT_EQ("int const&" , qualified_type_name<const int& >());
    ASSERT_EQ("int const&&", qualified_type_name<const int&&>());
    // should test for volatile as well, but meh
}

} // namespace fp::util
