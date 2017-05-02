#include <string>

#include <fp/util/named_tuple.h>

#include <catergorized_test.h>
#include <assert_same.h>
#include <assert_as_string.h>

#define TEST(what) CATEGORIZED_TEST(util, named_tuple, what)

namespace fp::util {

NAMED_TUPLE(person, (std::string, name)(size_t, born_in));

TEST(basic_usage) {
    person p("Bjarne Stroustrup", 1950);
    ASSERT_EQ("Bjarne Stroustrup", p.name);
    ASSERT_EQ(1950, p.born_in);
    ASSERT_SAME(std::string, person::name_t);
    ASSERT_SAME(size_t, person::born_in_t);
}

TEST(default_constructible) {
    person p;
    ASSERT_TRUE(p.name.empty());
}

// TEST(features_are_compiled_on_demand) {
    // The below code should compile successfully, even though `skinny` has no
    // default-constructor, no operator==, no operator<<, etc.
    struct skinny { skinny() = delete; };
    NAMED_TUPLE(has_skinny, (int, n)(skinny, s));
// }

TEST(constructible_from_convertible_types) {
    const char* name = "Bjarne Stroustrup";
    uint16_t born_in = 1950;
    person p(name, born_in);
    ASSERT_EQ("Bjarne Stroustrup", p.name);
    ASSERT_EQ(1950, p.born_in);
}

TEST(equality_comparable) {
    person p1("Bjarne Stroustrup", 1950);
    person p2("Bjarne Stroustrup", 1951);
    ASSERT_FALSE(p1 == p2);

    p2.born_in = 1950;
    ASSERT_TRUE(p1 == p2);
}

TEST(ostreamable) {
    person p("Bjarne Stroustrup", 1950);
    ASSERT_AS_STRING("person { name: Bjarne Stroustrup; born_in: 1950; }", p);
}

template <class T>
NAMED_TUPLE(point, (T, x)(T, y)(T, z));

TEST(supports_templates) {
    point<int> p1(1, 2, 3);
    ASSERT_AS_STRING("point { x: 1; y: 2; z: 3; }", p1);

    point<double> p2(2.71, 3.14, 4);
    ASSERT_AS_STRING("point { x: 2.71; y: 3.14; z: 4; }", p2);
}

} // namespace fp::util
