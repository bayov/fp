#pragma once

#include <type_traits>

namespace fp::util {

/**
 * A class wrapper over C++ fundamental types (which can be inherited from).
 *
 * @tparam T
 *      The type to wrap. Must be fundamental (`std::is_fundamental_v<T>`).
 */
template <class T>
class fundamental {
public:

    static_assert(std::is_fundamental_v<T>, "T must be fundamental");

    using type = T;

    constexpr fundamental() noexcept = default;
    constexpr fundamental(T value) noexcept : m_value(value) {}

    constexpr operator T() const noexcept { return m_value; }

private:

    T m_value;

};

template <> struct fundamental<void> { using type = void; };

template <>
struct fundamental<std::nullptr_t> {

    using type = std::nullptr_t;

    constexpr fundamental() noexcept = default;
    constexpr fundamental(std::nullptr_t) noexcept {}

    constexpr operator std::nullptr_t() const noexcept { return nullptr; }

};

} // namespace fp::util
