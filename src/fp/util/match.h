#pragma once

#include <variant>

#include <fp/util/overloaded.h>

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

} // namespace detail

/**
 * Syntax sugar over std::variant matching (std::visit).
 *
 * @example
 *
 *      std::variant<int, std::string> w("hello");
 *
 *      auto s = match(w)(
 *          [](int) { return "int"; }
 *          [](std::string) { return "string"; }
 *      );
 *      assert(s == "string");
 *
 * @note
 *      Use `[](auto&&) { ... }` for an "otherwise-match-clause".
 */
template <class Variant>
constexpr detail::matcher<Variant> match(const Variant& v) {
    return detail::matcher<Variant>(v);
}

} // namespace fp::util
