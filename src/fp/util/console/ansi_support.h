#pragma once

#include <fp/util/context_value.h>

namespace fp::util::console {

/// Returns `true` if the output-stream (std::cout) supports ANSI escape codes.
bool is_ansi_terminal_available();

/**
 * Returns `true` if ANSI escape codes are currently enabled.
 *
 * ANSI is initially enabled when console::is_ansi_terminal_available() returns
 * `true`. It can be disabled or enabled manually by calling
 * console::disable_ansi_globally() or console::enable_ansi_globally().
 *
 * This global state can be overridden in local contexts by assigning `true` or
 * `false` to console::use_ansi (this override mechanism is thread-local).
 *
 * Example:
 * ~~~{.cpp}
 * // assume color support is initially enabled
 * assert(console::ansi_enabled() == true);
 *
 * console::disable_ansi_globally();
 * assert(console::ansi_enabled() == false);
 *
 * // enable locally (for current thread only)
 * FP_WITH(console::use_ansi = true) {
 *     assert(console::ansi_enabled() == true);
 * }
 * // previous state is restored when going out of scope
 * assert(console::ansi_enabled() == false);
 * ~~~
 */
bool ansi_enabled();

//@{
/// See color::enabled().
void enable_ansi_globally();
void disable_ansi_globally();
extern thread_local context_value<const bool> use_ansi;
//@}

} // namespace fp::util::console
