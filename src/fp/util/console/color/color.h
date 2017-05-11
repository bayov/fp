#pragma once

#include <cstddef>
#include <ostream>

#include <fp/util/console/color/support.h>

namespace fp::util::console::color {

/// An ostream-able ansi color escape code.
struct code { size_t number; };

inline std::ostream& operator<<(std::ostream& os, code c) {
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
struct value {
    size_t open;
    size_t close;

    constexpr value(size_t o, size_t c) : open(o), close(c) {}

    /// Wraps `T`, enabling it to be ostream-ed with color escape codes.
    template <class T>
    struct wrapper {
        const value& c;
        const T& v;
    };

    template <class T>
    constexpr wrapper<T> operator()(const T& v) const { return { *this, v }; }

    /// Enable coloring in entire scope (using RAII).
    struct color_in_scope {
        const value& c;
        std::ostream& os;

        color_in_scope(const value& v, std::ostream& os) : c(v), os(os) {
            os << code { v.open };
        }

        ~color_in_scope() { os << code { c.close }; }

    };

    color_in_scope in_scope(std::ostream& os) const {
        return { *this, os };
    }
};

template <class T>
std::ostream& operator<<(std::ostream& os, value::wrapper<T> w) {
    return os << code { w.c.open } << w.v << code { w.c.close };
}

constexpr auto bold =           value(1, 22);
constexpr auto dim =            value(2, 22);
constexpr auto italic =         value(3, 23);
constexpr auto underline =      value(4, 24);
constexpr auto inverse =        value(7, 27);
constexpr auto hidden =         value(8, 28);
constexpr auto strikethrough =  value(9, 29);

constexpr auto black =          value(30, 39);
constexpr auto red =            value(31, 39);
constexpr auto green =          value(32, 39);
constexpr auto yellow =         value(33, 39);
constexpr auto blue =           value(34, 39);
constexpr auto magenta =        value(35, 39);
constexpr auto cyan =           value(36, 39);
constexpr auto white =          value(37, 39);
constexpr auto normal =         value(39, 39);

namespace bright {
constexpr auto black =          value(90, 39);
constexpr auto red =            value(91, 39);
constexpr auto green =          value(92, 39);
constexpr auto yellow =         value(93, 39);
constexpr auto blue =           value(94, 39);
constexpr auto magenta =        value(95, 39);
constexpr auto cyan =           value(96, 39);
constexpr auto white =          value(97, 39);
} // namespace bright

namespace bg {
constexpr auto black =          value(40, 49);
constexpr auto red =            value(41, 49);
constexpr auto green =          value(42, 49);
constexpr auto yellow =         value(43, 49);
constexpr auto blue =           value(44, 49);
constexpr auto magenta =        value(45, 49);
constexpr auto cyan =           value(46, 49);
constexpr auto white =          value(47, 49);
} // namespace bg

namespace bg::bright {
constexpr auto black =          value(100, 49);
constexpr auto red =            value(101, 49);
constexpr auto green =          value(102, 49);
constexpr auto yellow =         value(103, 49);
constexpr auto blue =           value(104, 49);
constexpr auto magenta =        value(105, 49);
constexpr auto cyan =           value(106, 49);
constexpr auto white =          value(107, 49);
} // namespace bg::bright

// aliases
constexpr auto gray = bright::black;
constexpr auto grey = gray;
namespace bg { constexpr auto gray = bg::bright::black; }
namespace bg { constexpr auto grey = gray; }

} // namespace fp::util::console::color
