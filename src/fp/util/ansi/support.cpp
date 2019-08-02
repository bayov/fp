#include <cstdlib>
#include <regex>

#include "support.h"

namespace fp::util::ansi {

namespace detail {

static bool detect_availability() {
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

bool& is_enabled_flag() {
    static bool b = is_available();
    return b;
}

} // namespace detail

bool is_available() {
    static bool b = detail::detect_availability();
    return b;
}

bool is_enabled() { return use_in_context.get(); }

void enable_globally() { detail::is_enabled_flag() = true; }
void disable_globally() { detail::is_enabled_flag() = false; }

thread_local context_value<const bool>
use_in_context(detail::is_enabled_flag());

} // namespace fp::util::ansi
