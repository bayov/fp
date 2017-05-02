#pragma once

#include <cstddef>
#include <ostream>

#include <fp/util/color_support.h>

namespace fp::util::color {

namespace detail {

/// An ostream-able ansi color escape code.
template <size_t NUMBER> struct code {};

template <size_t NUMBER>
std::ostream& operator<<(std::ostream& os, code<NUMBER>) {
    if (!has_color_support()) { return os; }
    return os << "\033[" << NUMBER << 'm';
}

/// Wraps `T` in `Color`, causing it to be ostream-ed with color escape codes.
template <class T, class Color>
struct color_wrapper {
    using value_type = T;
    using color_type = Color;
    const T& value;
};

template <class T, class Color>
std::ostream& operator<<(std::ostream& os, color_wrapper<T, Color> c) {
    return os << code<Color::open>{} << c.value << code<Color::close>{};
}

template <size_t OPEN, size_t CLOSE>
struct color_codes {
    static constexpr size_t open = OPEN;
    static constexpr size_t close = CLOSE;

    template <class T>
    constexpr color_wrapper<T, color_codes> operator()(const T& v) const {
        return { v };
    }
};

} // namespace detail

constexpr auto bold =           detail::color_codes<1, 21>{};
constexpr auto dim =            detail::color_codes<2, 22>{};
constexpr auto italic =         detail::color_codes<3, 23>{};
constexpr auto underline =      detail::color_codes<4, 24>{};
constexpr auto inverse =        detail::color_codes<7, 27>{};
constexpr auto hidden =         detail::color_codes<8, 28>{};
constexpr auto strikethrough =  detail::color_codes<9, 29>{};

constexpr auto black =          detail::color_codes<30, 39>{};
constexpr auto red =            detail::color_codes<31, 39>{};
constexpr auto green =          detail::color_codes<32, 39>{};
constexpr auto yellow =         detail::color_codes<33, 39>{};
constexpr auto blue =           detail::color_codes<34, 39>{};
constexpr auto magenta =        detail::color_codes<35, 39>{};
constexpr auto cyan =           detail::color_codes<36, 39>{};
constexpr auto white =          detail::color_codes<37, 39>{};

namespace bright {
constexpr auto black =          detail::color_codes<90, 39>{};
constexpr auto red =            detail::color_codes<91, 39>{};
constexpr auto green =          detail::color_codes<92, 39>{};
constexpr auto yellow =         detail::color_codes<93, 39>{};
constexpr auto blue =           detail::color_codes<94, 39>{};
constexpr auto magenta =        detail::color_codes<95, 39>{};
constexpr auto cyan =           detail::color_codes<96, 39>{};
constexpr auto white =          detail::color_codes<97, 39>{};
} // namespace bright

namespace bg {
constexpr auto black =          detail::color_codes<40, 49>{};
constexpr auto red =            detail::color_codes<41, 49>{};
constexpr auto green =          detail::color_codes<42, 49>{};
constexpr auto yellow =         detail::color_codes<43, 49>{};
constexpr auto blue =           detail::color_codes<44, 49>{};
constexpr auto magenta =        detail::color_codes<45, 49>{};
constexpr auto cyan =           detail::color_codes<46, 49>{};
constexpr auto white =          detail::color_codes<47, 49>{};
} // namespace bg

namespace bg::bright {
constexpr auto black =          detail::color_codes<100, 49>{};
constexpr auto red =            detail::color_codes<101, 49>{};
constexpr auto green =          detail::color_codes<102, 49>{};
constexpr auto yellow =         detail::color_codes<103, 49>{};
constexpr auto blue =           detail::color_codes<104, 49>{};
constexpr auto magenta =        detail::color_codes<105, 49>{};
constexpr auto cyan =           detail::color_codes<106, 49>{};
constexpr auto white =          detail::color_codes<107, 49>{};
} // namespace bg::bright

} // namespace fp::util::color
