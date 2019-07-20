#include <gtest/gtest.h>

#include <fp/util/record.h>
#include <fp/util/to_string.h>

#include <test-util/assert_type_eq.h>

namespace fp::util {

FP_RECORD(person, (std::string, name)(size_t, born_in));

TEST(util_record, basic_usage) {
    person p { .name = "Bjarne Stroustrup", .born_in = 1950 };
    ASSERT_EQ("Bjarne Stroustrup", p.name);
    ASSERT_EQ(1950u, p.born_in);
    ASSERT_TYPE_EQ(std::string, person::name_t);
    ASSERT_TYPE_EQ(size_t, person::born_in_t);
}

TEST(util_record, equality_comparable) {
    person p1 { .name = "Bjarne Stroustrup", .born_in = 1950 };
    person p2 { .name = "Bjarne Stroustrup", .born_in = 1951 };
    ASSERT_FALSE(p1 == p2);

    p2.born_in = 1950;
    ASSERT_TRUE(p1 == p2);
}

TEST(util_record, ostreamable) {
    person p { .name = "Bjarne Stroustrup", .born_in = 1950 };
    ASSERT_EQ("{ name: Bjarne Stroustrup, born_in: 1950 }", to_string(p));
}

// The below code should compile successfully, even though `skinny` has no
// default-constructor, no operator==, no operator<<, etc.
struct skinny { skinny() = delete; };
struct record_with_skinny {
    FP_RECORD_FIELDS(record_with_skinny, (skinny, s)(int, n));
};

} // namespace fp::util
