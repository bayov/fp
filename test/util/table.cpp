#include <gtest/gtest.h>

#include <fp/util/table.h>

namespace fp::util {

using handler_t = int (*)(int);

int as_is(int n) { return n; }
int plus_one(int n) { return n + 1; }
int times_two(int n) { return 2 * n; }

constexpr auto my_dispatch_table = table<char, handler_t, 100>([](auto& t) {
    t.set_default(as_is);
    t['1'] = plus_one;
    t['*'] = times_two;
});

TEST(util_table, basic_usage) {
    ASSERT_EQ(42, my_dispatch_table['c'](42));
    ASSERT_EQ(43, my_dispatch_table['1'](42));
    ASSERT_EQ(84, my_dispatch_table['*'](42));
}

struct modulus_50_index {
    constexpr size_t operator()(int key) const {
        // positive modulo
        int index = key % 50;
        if (index < 0) { index += 50; }
        return index;
    }
};

constexpr auto my_string_table =
    table<int, std::string_view, 50, modulus_50_index>([](auto& t) {
        t.set_default("default-value");
        t[42] = "forty-two";
        t[24] = "twenty-four";
    });

TEST(util_table, of_values_with_key_index) {
    ASSERT_EQ("default-value", my_string_table[11]);
    ASSERT_EQ("default-value", my_string_table[111]);
    ASSERT_EQ("forty-two"    , my_string_table[42]);
    ASSERT_EQ("forty-two"    , my_string_table[42 + 50]);
    ASSERT_EQ("twenty-four"  , my_string_table[24]);
    ASSERT_EQ("twenty-four"  , my_string_table[24 - 50]);
}

} // namespace fp::util
