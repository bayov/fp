#pragma once

#include <variant>

#include "overloaded.h"

namespace fp::util {

namespace detail {

template <class Variant>
class matcher {
public:

    constexpr explicit matcher(const Variant& v) : m_variant(v) {}

    template <class... Fs>
    constexpr auto operator()(Fs&&... fs) {
        return std::visit(overloaded(std::forward<Fs>(fs)...), m_variant);
    }

private:

    const Variant& m_variant;

};

} // detail

/**
 * Syntax sugar over std::variant matching (visiting):
 *
 * @example
 *
 *      std::variant<int, std::string> w("hello");
 *
 *      auto s = match(w)(
 *          [](int) { return "int"; }
 *          [](std::string) { return "string"; }
 *      );
 *      // s == "string"
 *
 * @note
 *      Use `[](auto&&) { ... }` for an "otherwise-match-clause".
 */
template <class Variant>
constexpr detail::matcher<Variant> match(const Variant& v) {
    return detail::matcher<Variant>(v);
}

} // fp::util
