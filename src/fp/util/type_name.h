#pragma once

#include <string_view>

namespace fp::util {

namespace detail {

template <class T>
constexpr std::string_view type_name() {
#if defined(__GNUC__) && __GNUC__ >= 9
    std::string_view name(__PRETTY_FUNCTION__);
    name = name.substr(sizeof(
        "constexpr std::string_view fp::util::detail::type_name() [with T ="
    ));
    size_t i = 1;
    while (name[i] != ';') { ++i; }
    return name.substr(0, i);
#else
    static_assert(false, "Unsupported compiler");
#endif
}

} // namespace detail

/// The name of the given type `T`.
template <class T>
constexpr std::string_view type_name = detail::type_name<T>();

} // namespace fp::util
