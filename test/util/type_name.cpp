#include <fp/util/type_name.h>

#include <test-util/catergorized_test.h>

namespace fp::util {

#define TEST(what) CATEGORIZED_TEST(util, type_name, what)

TEST(of_value) { ASSERT_EQ("int", type_name(42)); }

TEST(of_type) { ASSERT_EQ("int", type_name<int>()); }

template <class T> struct foo {};
TEST(of_template) { ASSERT_EQ("fp::util::foo<int>", type_name<foo<int>>()); }

TEST(of_qualified_types) {
    ASSERT_EQ("int&"       , qualified_type_name<int&       >());
    ASSERT_EQ("int&&"      , qualified_type_name<int&&      >());
    ASSERT_EQ("int const"  , qualified_type_name<const int  >());
    ASSERT_EQ("int const&" , qualified_type_name<const int& >());
    ASSERT_EQ("int const&&", qualified_type_name<const int&&>());
    // should test for volatile as well, but meh
}

} // namespace fp::util
