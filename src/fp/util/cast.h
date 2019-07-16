#pragma once

#include <utility>

namespace fp::util {

/// A simple functor that explicitly casts to `T`.
template <class T>
struct cast {
    template <class U>
    constexpr T operator()(U&& v) const { return T(std::forward<U>(v)); }
};

} // namespace fp::util
