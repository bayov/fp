#include <cstdlib>
#include <regex>

#include "ansi_support.h"

namespace fp::util::console {

namespace detail {

static bool detect_ansi_support() {
    auto term = std::getenv("TERM");
    if (term) {
        static std::regex term_regex(
            "^screen|^xterm|^vt100|color|ansi|cygwin|linux",
            std::regex::icase
        );
        if (std::regex_search(term, term_regex)) {
            return true;
        }
    }
    if (std::getenv("COLORTERM")) { return true; }
    if (std::getenv("FORCE_COLOR")) { return true; }
    return false;
}

bool& ansi_enable_flag() {
    static bool b = is_ansi_terminal_available();
    return b;
}

} // namespace detail

bool is_ansi_terminal_available() {
    static bool b = detail::detect_ansi_support();
    return b;
}

bool ansi_enabled() { return use_ansi.get(); }

void enable_ansi_globally() { detail::ansi_enable_flag() = true; }
void disable_ansi_globally() { detail::ansi_enable_flag() = false; }

thread_local context_value<const bool> use_ansi(detail::ansi_enable_flag());

} // namespace fp::util::console
