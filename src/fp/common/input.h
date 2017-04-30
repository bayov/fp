#pragma once

#include <string_view>

#include <fp/common/types.h>

namespace fp {

/// Represents a source file (as a string of @ref symbol_t).
using input = std::basic_string<symbol_t>;

/// A slice of an @ref input.
struct input_view : std::basic_string_view<symbol_t> {
    using std::basic_string_view<symbol_t>::basic_string_view;
    input_view(iterator begin, iterator end);
    input_view(const input& in);
};

/// An iterator to a @ref symbol_t in an @ref input_view.
using symbol_iterator = input_view::const_iterator;

} // namespace fp

namespace std {

template <>
struct hash<fp::input_view> : hash<std::basic_string_view<fp::symbol_t>> {};

} // std
