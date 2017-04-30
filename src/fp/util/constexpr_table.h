#pragma once

#include <array>

#include "cast.h"

namespace fp::util {

namespace detail {

template <auto VALUE>
struct default_value {
    static constexpr auto value = VALUE;
};

template <auto KEY, auto VALUE>
struct assigned_value {
    static constexpr auto key = KEY;
    static constexpr auto value = VALUE;
};

} // detail

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
 *      using my_table = constexpr_table<char, handler_t, 100>
 *          ::set_default<as_is>
 *          ::set<'1', plus_one>
 *          ::set<'*', times_two>;
 *
 *      my_table::get('c')(42); // == 42  (uses `as_is`)
 *      my_table::get('1')(42); // == 43  (uses `plus_one`)
 *      my_table::get('*')(42); // == 84  (uses `times_two`)
 *
 *      // the table's size is 100 (up to `c`), meaning `d` cannot be used as
 *      // a key. Doing so will result in undefined behaviour!
 *      my_table::get('d'); // `d` == 100 --> out of range!
 *
 * @tparam TransformKey
 *      An optional functor that can be applied to transform the key to a
 *      `size_t` before using it.
 */
template <
    class Key,
    class Value,
    size_t SIZE,
    class TransformKey = cast<size_t>,
    class DefaultValue = void,
    class... Values
>
struct constexpr_table {

    template <Value VALUE>
    using set_default = constexpr_table<
        Key,
        Value,
        SIZE,
        TransformKey,
        detail::default_value<VALUE>
    >;

};

template <
    class Key,
    class Value,
    size_t SIZE,
    class TransformKey,
    Value DEFAULT_VALUE,
    class... Values
>
class constexpr_table<
    Key,
    Value,
    SIZE,
    TransformKey,
    detail::default_value<DEFAULT_VALUE>,
    Values...
> {
public:

    using key_type = Key;
    using value_type = Value;
    using transform_key_t = TransformKey;

    static constexpr size_t size = SIZE;
    static constexpr auto default_value = DEFAULT_VALUE;

    template <Key KEY, Value VALUE>
    using set = constexpr_table<
        Key,
        Value,
        SIZE,
        TransformKey,
        detail::default_value<DEFAULT_VALUE>,
        Values...,
        detail::assigned_value<KEY, VALUE>
    >;

    static Value get(Key key) {
        static const auto table = create_table();
        return table[TransformKey{}(key)];
    }

    template <Key KEY>
    static constexpr Value get() { return create_table()[TransformKey{}(KEY)]; }

private:

    static constexpr std::array<Value, SIZE> create_table() {
        std::array<Value, SIZE> table = {};
        for (auto& value : table) { value = DEFAULT_VALUE; }
        (... , (table[TransformKey{}(Values::key)] = Values::value));
        return table;
    }

};

} // fp::util
