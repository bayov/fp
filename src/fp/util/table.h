#pragma once

#include <array>

#include <fp/util/cast.h>

namespace fp::util {

/**
 * Create a compile time table mapping from keys to values.
 *
 * The values can be function-pointers to create a dispatch table.
 *
 * @example
 *
 *      using handler_t = int (*)(int);
 *
 *      int as_is(int n) { return n; }
 *      int plus_one(int n) { return n + 1; }
 *      int times_two(int n) { return 2 * n; }
 *
 *      constexpr auto my_table = ([]() {
 *          auto t = table<char, handler_t, 100>::with_default(as_is);
 *          t['1'] = plus_one;
 *          t['2'] = times_two;
 *      })();
 *
 *      my_table['c'](42); // == 42  (uses `as_is`)
 *      my_table['1'](42); // == 43  (uses `plus_one`)
 *      my_table['*'](42); // == 84  (uses `times_two`)
 *
 *      // the table's size is 100 (up to `c`), meaning `d` cannot be used as
 *      // a key. Doing so will result in undefined behaviour!
 *      my_table['d']; // `d` == 100 --> out of range!
 *
 * @tparam KeyIndex
 *      An optional functor that will be applied to transform the key to a
 *      a `size_t` index before using it.
 */
template <class Key, class Value, size_t SIZE, class KeyIndex = cast<size_t>>
class table {
public:

    using key_type = Key;
    using value_type = Value;

    static constexpr table with_default(Value default_value) {
        table t;
        for (auto& v : t.m_values) { v = default_value; }
        return t;
    }

    constexpr size_t size() const { return m_values.size(); }

    constexpr value_type& operator[](Key key) {
        return m_values[KeyIndex{}(key)];
    }

    constexpr const value_type& operator[](Key key) const {
        return m_values[KeyIndex{}(key)];
    }

private:

    std::array<Value, SIZE> m_values = {};

    constexpr table() = default;

};

} // namespace fp::util
