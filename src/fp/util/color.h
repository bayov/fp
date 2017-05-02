#pragma once

#include <cstddef>
#include <ostream>
#include <unistd.h>

namespace fp::util {

namespace detail {

inline bool& has_color_support() {
    // TODO: improve color support detection...
    static bool b = bool(isatty(fileno(stdout)));
    return b;
}

constexpr auto ANSI_PREFIX = "\u001B[";
constexpr auto ANSI_SUFFIX = "m";

template <class T, class Color>
struct color_wrapper {
    using value_type = T;
    using color_type = Color;
    const T& value;
};

template <class T, class Color>
std::ostream& operator<<(std::ostream& os, color_wrapper<T, Color> c) {
    if (has_color_support()) {
        os << detail::ANSI_PREFIX << Color::open << detail::ANSI_SUFFIX;
    }
    os << c.value;
    if (has_color_support()) {
        os << detail::ANSI_PREFIX << Color::close << detail::ANSI_SUFFIX;
    }
    return os;
}

template <size_t OPEN, size_t CLOSE>
struct ansi_color_code {
    static constexpr size_t open = OPEN;
    static constexpr size_t close = CLOSE;

    template <class T>
    constexpr color_wrapper<T, ansi_color_code> operator()(const T& v) const {
        return { v };
    }
};

} // namespace detail

namespace color {

/// Forcebly enable printing of color escape codes (non-thread-safe).
inline void enable() { detail::has_color_support() = true; }

/// Forcebly disable printing of color escape codes (non-thread-safe).
inline void disable() { detail::has_color_support() = false; }

constexpr auto bold =           detail::ansi_color_code<1, 21>{};
constexpr auto dim =            detail::ansi_color_code<2, 22>{};
constexpr auto italic =         detail::ansi_color_code<3, 23>{};
constexpr auto underline =      detail::ansi_color_code<4, 24>{};
constexpr auto inverse =        detail::ansi_color_code<7, 27>{};
constexpr auto hidden =         detail::ansi_color_code<8, 28>{};
constexpr auto strikethrough =  detail::ansi_color_code<9, 29>{};

constexpr auto black =          detail::ansi_color_code<30, 39>{};
constexpr auto red =            detail::ansi_color_code<31, 39>{};
constexpr auto green =          detail::ansi_color_code<32, 39>{};
constexpr auto yellow =         detail::ansi_color_code<33, 39>{};
constexpr auto blue =           detail::ansi_color_code<34, 39>{};
constexpr auto magenta =        detail::ansi_color_code<35, 39>{};
constexpr auto cyan =           detail::ansi_color_code<36, 39>{};
constexpr auto white =          detail::ansi_color_code<37, 39>{};

} // namespace color

namespace color::bright {

constexpr auto black =          detail::ansi_color_code<90, 39>{};
constexpr auto red =            detail::ansi_color_code<91, 39>{};
constexpr auto green =          detail::ansi_color_code<92, 39>{};
constexpr auto yellow =         detail::ansi_color_code<93, 39>{};
constexpr auto blue =           detail::ansi_color_code<94, 39>{};
constexpr auto magenta =        detail::ansi_color_code<95, 39>{};
constexpr auto cyan =           detail::ansi_color_code<96, 39>{};
constexpr auto white =          detail::ansi_color_code<97, 39>{};

} // namespace color::bright

namespace color::bg {

constexpr auto black =          detail::ansi_color_code<40, 49>{};
constexpr auto red =            detail::ansi_color_code<41, 49>{};
constexpr auto green =          detail::ansi_color_code<42, 49>{};
constexpr auto yellow =         detail::ansi_color_code<43, 49>{};
constexpr auto blue =           detail::ansi_color_code<44, 49>{};
constexpr auto magenta =        detail::ansi_color_code<45, 49>{};
constexpr auto cyan =           detail::ansi_color_code<46, 49>{};
constexpr auto white =          detail::ansi_color_code<47, 49>{};

} // namespace color::bg

namespace color::bg::bright {

constexpr auto black =          detail::ansi_color_code<100, 49>{};
constexpr auto red =            detail::ansi_color_code<101, 49>{};
constexpr auto green =          detail::ansi_color_code<102, 49>{};
constexpr auto yellow =         detail::ansi_color_code<103, 49>{};
constexpr auto blue =           detail::ansi_color_code<104, 49>{};
constexpr auto magenta =        detail::ansi_color_code<105, 49>{};
constexpr auto cyan =           detail::ansi_color_code<106, 49>{};
constexpr auto white =          detail::ansi_color_code<107, 49>{};

} // namespace color::bg::bright

} // namespace fp::util
