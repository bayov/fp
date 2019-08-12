#pragma once

#include <variant>

#include <fp/util/overloaded.h>

namespace fp::util {

namespace detail {

template <class Variant>
struct matcher {
    constexpr explicit matcher(Variant v)
        : variant_(std::forward<Variant>(v)) {}

    template <class... Fs>
    constexpr decltype(auto) operator()(Fs&&... fs) && {
        return std::visit(
            overloaded { std::forward<Fs>(fs)... },
            std::forward<Variant>(variant_)
        );
    }

private:
    Variant variant_;
};

} // namespace detail

/**
 * Syntax sugar over std::variant matching (std::visit and util::overloaded).
 *
 * ~~~{.cpp}
 * std::variant<int, std::string> w("hello");
 *
 * auto s = match(w)(
 *     [](int) { return "int"; },
 *     [](std::string) { return "string"; }
 * );
 * assert(s == "string");
 * ~~~
 *
 * Note: `[](auto&&) { ... }` can be used as a "default match clause".
 */
template <class Variant>
constexpr detail::matcher<Variant> match(Variant&& v) {
    return detail::matcher<Variant>(std::forward<Variant>(v));
}

} // namespace fp::util
