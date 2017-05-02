#pragma once

#include <cstdlib>
#include <regex>

namespace fp::util::color {

namespace detail {

/**
 * Detect whether we're running with support for ansi color escape codes.
 *
 * @todo
 *      Improve detection...
 */
inline bool detect_color_support() {
    auto term = std::getenv("TERM");
    if (term) {
        std::regex term_regex(
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

/// @return `true` if color is enabled globally.
inline bool& enabled() {
    static bool b = detect_color_support();
    return b;
}

/// @see force_in_scope_base
inline bool& force_enabled_in_thread() {
    static thread_local bool b = false;
    return b;
}

/// @see force_in_scope_base
inline bool& force_disabled_in_thread() {
    static thread_local bool b = false;
    return b;
}

/// @return `true` if color is enabled in the current scope.
inline bool has_color_support() {
    if (force_enabled_in_thread()) { return true; }
    if (force_disabled_in_thread()) { return false; }
    return enabled();
}

/// Base class for @ref enable_in_scope and @ref disable_in_scope.
class force_in_scope_base {
public:

    force_in_scope_base() :
        m_previously_force_enabled(detail::force_enabled_in_thread()),
        m_previously_force_disabled(detail::force_disabled_in_thread())
    {}

    ~force_in_scope_base() {
        detail::force_enabled_in_thread() = m_previously_force_enabled;
        detail::force_enabled_in_thread() = m_previously_force_disabled;
    }

private:

    bool m_previously_force_enabled;
    bool m_previously_force_disabled;

};

} // namespace detail

/// Forcibly enable printing of color escape codes (not thread-safe).
inline void enable() { detail::enabled() = true; }

/// Forcibly disable printing of color escape codes (not thread-safe).
inline void disable() { detail::enabled() = false; }

/**
 * Forcibly enable colors, RAII style. This call is both thread-safe, and works
 * well with recursions to any depth (together with @ref disable_in_scope).
 */
struct enable_in_scope : detail::force_in_scope_base {
    enable_in_scope(bool enable = true) {
        if (enable) { detail::force_enabled_in_thread() = true; }
    }
};

/**
 * Forcibly disable colors, RAII style. This call is both thread-safe, and works
 * well with recursions to any depth (together with @ref enable_in_scope).
 */
struct disable_in_scope : detail::force_in_scope_base {
    disable_in_scope(bool disable = true) {
        if (disable) { detail::force_disabled_in_thread() = true; }
    }
};

} // namespace fp::util::color
