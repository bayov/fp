#pragma once

#include <cstddef>
#include <array>

#include <fp/util/cast.h>

namespace fp::util {

/**
 * Used to construct compile-time mappings from keys to values.
 *
 * The values can be function-pointers to create a dispatch table.
 *
 * ~~~{.cpp}
 * using handler_t = int (*)(int);
 *
 * int as_is    (int n) { return n;     }
 * int plus_one (int n) { return n + 1; }
 * int times_two(int n) { return 2 * n; }
 *
 * constexpr auto my_dispatch_table =
 *     util::table<char, handler_t, 100>([](auto& t) {
 *         t.set_default(as_is); // sets all 100 cells to the `as_is` function
 *         t['1'] = plus_one;
 *         t['2'] = times_two;
 *     });
 *
 * my_dispatch_table['c'](42); // == 42  (uses `as_is`)
 * my_dispatch_table['1'](42); // == 43  (uses `plus_one`)
 * my_dispatch_table['2'](42); // == 84  (uses `times_two`)
 * ~~~
 *
 * In the example above, `my_dispatch_table` is stored in the data section of
 * the executable as 100 consecutive `handler_t` pointers, and `operator[]` is
 * used to access those values directly (by `t[size_t(key)]`). Basically, a
 * dispatch table with no overhead at all.
 *
 * Note that in the example above, the size of `my_dispatch_table` is 100, and
 * the ASCII value of 'c' is 99, which means that 'd' cannot be given as a key.
 * Doing so will result in undefined behaviour.
 *
 * @tparam KeyIndex
 *      An optional function that takes a `Key` and returns `size_t` index for
 *      it to look up inside the table. By default, the key will be casted using
 *      the expression `size_t(key)`.
 */
template <class Key, class Value, size_t SIZE, class KeyIndex = cast<size_t>>
struct table {
    using key_type    = Key;
    using value_type  = Value;
    using key_index_t = KeyIndex;

    static constexpr size_t      size      = SIZE;
    static constexpr key_index_t key_index = KeyIndex();

    template <class Constructor>
    explicit constexpr table(Constructor&& ctor) { ctor(*this); }

    /**
     * Overrides the value of all keys with `default_value`, so must be used
     * before any assignments to the table.
     */
    constexpr void set_default(Value default_value) {
        for (auto& v : values) { v = default_value; }
    }

    constexpr value_type& operator[](Key key) {
        return values[key_index(key)];
    }

    constexpr const value_type& operator[](Key key) const {
        return values[key_index(key)];
    }

private:
    std::array<Value, SIZE> values = {};
};

} // namespace fp::util
