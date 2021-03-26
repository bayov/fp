#pragma once

#include <fp/util/context_value.h>

namespace fp::util::ansi {

/// Returns `true` if the output-stream (std::cout) supports ANSI escape codes.
bool is_available();

/**
 * Returns `true` if ANSI escape codes are currently enabled.
 *
 * ANSI is initially enabled when ansi::is_available() returns `true`. It can be
 * disabled or enabled manually by calling ansi::disable_globally() or
 * ansi::enable_globally().
 *
 * Escape codes can also be enabled by running with environment variable
 * `FORCE_COLOR` set.
 *
 * This global state can be overridden in local contexts by assigning `true` or
 * `false` to ansi::enable_in_context (this override mechanism is thread-local).
 *
 * Example:
 * ~~~{.cpp}
 * // assume std::cout ANSI supported is detected
 * assert(ansi::is_available() == true);
 *
 * // meaning, by default, ANSI escape-codes are enabled
 * assert(ansi::is_enabled() == true);
 *
 * ansi::disable_globally();
 * assert(ansi::is_enabled() == false);
 *
 * // enable locally (for current thread only)
 * FP_WITH(ansi::enable_in_context = true) {
 *     assert(ansi::is_enabled() == true);
 * }
 * // previous state is restored when going out of scope
 * assert(ansi::ansi_enabled() == false);
 * ~~~
 */
bool is_enabled();

//@{
/// See ansi::is_enabled().
void enable_globally();
void disable_globally();
extern thread_local context_value<const bool> enable_in_context;
//@}

} // namespace fp::util::ansi
