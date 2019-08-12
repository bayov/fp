#pragma once

#include <cstddef>
#include <ostream>

#include <fp/util/ansi/support.h>

namespace fp::util::ansi {

/// An ostream-able ANSI graphics mode escape code (`Esc[<value>m`).
struct graphics_code { uint8_t number; };

inline std::ostream& operator<<(std::ostream& os, graphics_code c) {
    if (!ansi::is_enabled()) { return os; }
    return os << "\033[" << uint16_t(c.number) << 'm';
}

inline bool operator==(graphics_code c1, graphics_code c2) {
    return c1.number == c2.number;
}
inline bool operator!=(graphics_code c1, graphics_code c2) { return !(c1 == c2); }

constexpr auto reset             = graphics_code {   0 };
constexpr auto bold              = graphics_code {   1 };
constexpr auto faint             = graphics_code {   2 };
constexpr auto italic            = graphics_code {   3 };
constexpr auto underline         = graphics_code {   4 };
constexpr auto blink             = graphics_code {   5 };
constexpr auto inverse           = graphics_code {   7 };
constexpr auto conceal           = graphics_code {   8 };
constexpr auto strikethrough     = graphics_code {   9 };
constexpr auto normal            = graphics_code {  10 };
constexpr auto italic_off        = graphics_code {  23 };
constexpr auto underline_off     = graphics_code {  24 };
constexpr auto blink_off         = graphics_code {  25 };
constexpr auto inverse_off       = graphics_code {  27 };
constexpr auto conceal_off       = graphics_code {  28 };
constexpr auto strikethrough_off = graphics_code {  29 };

constexpr auto black             = graphics_code {  30 };
constexpr auto red               = graphics_code {  31 };
constexpr auto green             = graphics_code {  32 };
constexpr auto yellow            = graphics_code {  33 };
constexpr auto blue              = graphics_code {  34 };
constexpr auto magenta           = graphics_code {  35 };
constexpr auto cyan              = graphics_code {  36 };
constexpr auto white             = graphics_code {  37 };
constexpr auto default_color     = graphics_code {  39 };

constexpr auto bg_black          = graphics_code {  40 };
constexpr auto bg_red            = graphics_code {  41 };
constexpr auto bg_green          = graphics_code {  42 };
constexpr auto bg_yellow         = graphics_code {  43 };
constexpr auto bg_blue           = graphics_code {  44 };
constexpr auto bg_magenta        = graphics_code {  45 };
constexpr auto bg_cyan           = graphics_code {  46 };
constexpr auto bg_white          = graphics_code {  47 };
constexpr auto bg_default_color  = graphics_code {  49 };

constexpr auto frame_start       = graphics_code {  51 };
constexpr auto frame_end         = graphics_code {  54 };

constexpr auto bright_black      = graphics_code {  90 };
constexpr auto grey              = bright_black;
constexpr auto bright_red        = graphics_code {  91 };
constexpr auto bright_green      = graphics_code {  92 };
constexpr auto bright_yellow     = graphics_code {  93 };
constexpr auto bright_blue       = graphics_code {  94 };
constexpr auto bright_magenta    = graphics_code {  95 };
constexpr auto bright_cyan       = graphics_code {  96 };
constexpr auto bright_white      = graphics_code {  97 };

constexpr auto bg_bright_black   = graphics_code { 100 };
constexpr auto bg_grey           = bg_bright_black;
constexpr auto bg_bright_red     = graphics_code { 101 };
constexpr auto bg_bright_green   = graphics_code { 102 };
constexpr auto bg_bright_yellow  = graphics_code { 103 };
constexpr auto bg_bright_blue    = graphics_code { 104 };
constexpr auto bg_bright_magenta = graphics_code { 105 };
constexpr auto bg_bright_cyan    = graphics_code { 106 };
constexpr auto bg_bright_white   = graphics_code { 107 };

} // namespace fp::util::ansi
