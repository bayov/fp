#pragma once

#include <utility>

namespace fp::util {

/// A simple functor that explicitly casts to `T`.
template <class T>
struct cast {
    template <class Arg>
    constexpr T operator()(Arg&& arg) const {
        return T(std::forward<Arg>(arg));
    }
};

} // namespace fp::util
