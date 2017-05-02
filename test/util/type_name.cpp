#include <fp/util/type_name.h>

#include <catergorized_test.h>

#define TEST(what) CATEGORIZED_TEST(util, type_name, what)

namespace fp::util {

TEST(of_value) { ASSERT_EQ("int", type_name(42)); }

TEST(of_type) { ASSERT_EQ("int", type_name<int>()); }

template <class T> struct foo {};

TEST(of_template) { ASSERT_EQ("fp::util::foo<int>", type_name<foo<int>>()); }

} // namespace fp::util
