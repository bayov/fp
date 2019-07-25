#pragma once

#include <cstddef>
#include <ostream>

#include <fp/util/console/ansi_support.h>

namespace fp::util::console {

/// An ostream-able ANSI graphics escape code (`Esc[<value>m`).
struct ansi_graphics_code { size_t number; };

inline std::ostream& operator<<(std::ostream& os, ansi_graphics_code c) {
    if (!ansi_enabled()) { return os; }
    return os << "\033[" << c.number << 'm';
}

/**
 * Represents an ANSI accent escape code (such as bold, italic, etc.), together
 * with its respective closing escape code that turns off the accent.
 *
 * Accent code constants are defined under console::accent.
 */
struct ansi_accent_code {
    ansi_graphics_code open;
    ansi_graphics_code close;
};

namespace accent {

constexpr auto bold          = ansi_accent_code { {1}, {22} };
constexpr auto dim           = ansi_accent_code { {2}, {22} };
constexpr auto italic        = ansi_accent_code { {3}, {23} };
constexpr auto underline     = ansi_accent_code { {4}, {24} };
constexpr auto inverse       = ansi_accent_code { {7}, {27} };
constexpr auto hidden        = ansi_accent_code { {8}, {28} };
constexpr auto strikethrough = ansi_accent_code { {9}, {29} };

} // namespace accent

/**
 * Represents an ANSI foreground color escape code.
 *
 * Foreground color code constants are defined under console::color. To reset to
 * the default foreground color, use color::default_.
 */
struct ansi_color_code : ansi_graphics_code {};

/**
 * Represents an ANSI background color escape code.
 *
 * Background color code constants are defined under console::color::bg. To
 * reset to the default background color, use color::bg::default_.
 */
struct ansi_bg_color_code : ansi_graphics_code {};

namespace color {

constexpr auto default_       = ansi_color_code {{ 39 }};
constexpr auto black          = ansi_color_code {{ 30 }};
constexpr auto red            = ansi_color_code {{ 31 }};
constexpr auto green          = ansi_color_code {{ 32 }};
constexpr auto yellow         = ansi_color_code {{ 33 }};
constexpr auto blue           = ansi_color_code {{ 34 }};
constexpr auto magenta        = ansi_color_code {{ 35 }};
constexpr auto cyan           = ansi_color_code {{ 36 }};
constexpr auto white          = ansi_color_code {{ 37 }};
constexpr auto bright_black   = ansi_color_code {{ 90 }};
constexpr auto grey           = bright_black;
constexpr auto bright_red     = ansi_color_code {{ 91 }};
constexpr auto bright_green   = ansi_color_code {{ 92 }};
constexpr auto bright_yellow  = ansi_color_code {{ 93 }};
constexpr auto bright_blue    = ansi_color_code {{ 94 }};
constexpr auto bright_magenta = ansi_color_code {{ 95 }};
constexpr auto bright_cyan    = ansi_color_code {{ 96 }};
constexpr auto bright_white   = ansi_color_code {{ 97 }};

} // namespace color

namespace color::bg {

constexpr auto default_       = ansi_color_code {{ 49  }};
constexpr auto black          = ansi_color_code {{ 40  }};
constexpr auto red            = ansi_color_code {{ 41  }};
constexpr auto green          = ansi_color_code {{ 42  }};
constexpr auto yellow         = ansi_color_code {{ 43  }};
constexpr auto blue           = ansi_color_code {{ 44  }};
constexpr auto magenta        = ansi_color_code {{ 45  }};
constexpr auto cyan           = ansi_color_code {{ 46  }};
constexpr auto white          = ansi_color_code {{ 47  }};
constexpr auto bright_black   = ansi_color_code {{ 100 }};
constexpr auto grey           = bright_black;
constexpr auto bright_red     = ansi_color_code {{ 101 }};
constexpr auto bright_green   = ansi_color_code {{ 102 }};
constexpr auto bright_yellow  = ansi_color_code {{ 103 }};
constexpr auto bright_blue    = ansi_color_code {{ 104 }};
constexpr auto bright_magenta = ansi_color_code {{ 105 }};
constexpr auto bright_cyan    = ansi_color_code {{ 106 }};
constexpr auto bright_white   = ansi_color_code {{ 107 }};

} // namespace color::bg

} // namespace fp::util::console
