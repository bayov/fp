#pragma once

#include <cstddef>
#include <ostream>

#include <fp/util/color_support.h>

namespace fp::util::color {

/// An ostream-able ansi color escape code.
struct color_code { size_t number; };

inline std::ostream& operator<<(std::ostream& os, color_code c) {
    if (!has_color_support()) { return os; }
    return os << "\033[" << c.number << 'm';
}

/**
 * A color has `open` and `close` ansi color escape codes.
 *
 * Use the constant colors values defined in namespace `fp::util::color` (i.e.,
 * bold, red, bg::yellow).
 *
 * Using `operator()` on a value will wrap it in `wrapper`, which will print the
 * color codes when ostream-ed.
 *
 * Using `in_scope(os)` will create a RAII-style mechanism that will print the
 * opening code when constructed, and the closing code when destructed.
 *
 * @example
 *
 *      using namespace fp::util::color;
 *      std::cout << bold("1 + 1 = ") << bright::green(2) << std::endl;
 *
 *      // using <fp/util/with.h>
 *      WITH(gray.in_scope(std::cout)) {
 *          std::cout << "all text here is gray" << std::endl;
 *      }
 */
struct color_value {
    size_t open;
    size_t close;

    constexpr color_value(size_t o, size_t c) : open(o), close(c) {}

    /// Wraps `T`, enabling it to be ostream-ed with color escape codes.
    template <class T>
    struct wrapper {
        const color_value& c;
        const T& value;
    };

    template <class T>
    constexpr wrapper<T> operator()(const T& v) const { return { *this, v }; }

    /// Enable coloring in entire scope (using RAII).
    struct color_in_scope {
        const color_value& c;
        std::ostream& os;

        color_in_scope(const color_value& c, std::ostream& os) : c(c), os(os) {
            os << color_code { c.open };
        }

        ~color_in_scope() { os << color_code { c.close }; }

    };

    color_in_scope in_scope(std::ostream& os) const {
        return { *this, os };
    }
};

template <class T>
std::ostream& operator<<(std::ostream& os, color_value::wrapper<T> w) {
    return os << color_code { w.c.open } << w.value << color_code { w.c.close };
}

constexpr auto bold =           color_value(1, 21);
constexpr auto dim =            color_value(2, 22);
constexpr auto italic =         color_value(3, 23);
constexpr auto underline =      color_value(4, 24);
constexpr auto inverse =        color_value(7, 27);
constexpr auto hidden =         color_value(8, 28);
constexpr auto strikethrough =  color_value(9, 29);

constexpr auto black =          color_value(30, 39);
constexpr auto red =            color_value(31, 39);
constexpr auto green =          color_value(32, 39);
constexpr auto yellow =         color_value(33, 39);
constexpr auto blue =           color_value(34, 39);
constexpr auto magenta =        color_value(35, 39);
constexpr auto cyan =           color_value(36, 39);
constexpr auto white =          color_value(37, 39);

namespace bright {
constexpr auto black =          color_value(90, 39);
constexpr auto red =            color_value(91, 39);
constexpr auto green =          color_value(92, 39);
constexpr auto yellow =         color_value(93, 39);
constexpr auto blue =           color_value(94, 39);
constexpr auto magenta =        color_value(95, 39);
constexpr auto cyan =           color_value(96, 39);
constexpr auto white =          color_value(97, 39);
} // namespace bright

namespace bg {
constexpr auto black =          color_value(40, 49);
constexpr auto red =            color_value(41, 49);
constexpr auto green =          color_value(42, 49);
constexpr auto yellow =         color_value(43, 49);
constexpr auto blue =           color_value(44, 49);
constexpr auto magenta =        color_value(45, 49);
constexpr auto cyan =           color_value(46, 49);
constexpr auto white =          color_value(47, 49);
} // namespace bg

namespace bg::bright {
constexpr auto black =          color_value(100, 49);
constexpr auto red =            color_value(101, 49);
constexpr auto green =          color_value(102, 49);
constexpr auto yellow =         color_value(103, 49);
constexpr auto blue =           color_value(104, 49);
constexpr auto magenta =        color_value(105, 49);
constexpr auto cyan =           color_value(106, 49);
constexpr auto white =          color_value(107, 49);
} // namespace bg::bright

// aliases
constexpr auto gray = bright::black;
constexpr auto grey = gray;
namespace bg { constexpr auto gray = bg::bright::black; }
namespace bg { constexpr auto grey = gray; }

} // namespace fp::util::color
