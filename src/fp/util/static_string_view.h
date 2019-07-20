#pragma once

#include <array>
#include <string_view>

namespace fp::util {

namespace detail {

/// A compile-time std::array containing the given `VALUES` of type `T`.
template <class T, T... VALUES>
constexpr std::array<T, sizeof...(VALUES)> static_array = { VALUES... };

} // namespace detail

/// A compile-time std::basic_string_view<Char> for the given `CHARS`.
template <class Char, Char... CHARS>
constexpr std::basic_string_view<Char> basic_static_string_view {
    detail::static_array<Char, CHARS...>.data(), sizeof...(CHARS)
};

} // namespace fp::util
