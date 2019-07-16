#pragma once

namespace fp::util {

template <class T>
struct type_constant { using type = T; };

/// An instance that represents a type. Useful when passing a type by argument.
template <class T>
constexpr type_constant<T> type_c{};

} // namespace fp::util
