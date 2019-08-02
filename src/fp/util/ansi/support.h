#pragma once

#include <fp/util/context_value.h>

namespace fp::util::ansi {

/// Returns `true` if the output-stream (std::cout) supports ANSI escape codes.
bool is_available();

/**
 * Returns `true` if ANSI escape codes are currently enabled.
 *
 * ANSI is initially enabled when util::is_available() return `true`. It can be
 * disabled or enabled manually by calling ansi::disable_globally() or
 * ansi::enable_globally().
 *
 * This global state can be overridden in local contexts by assigning `true` or
 * `false` to ansi::use_in_context (this override mechanism is thread-local).
 *
 * Example:
 * ~~~{.cpp}
 * // assume color support is initially enabled
 * assert(ansi::is_enabled() == true);
 *
 * ansi::disable_globally();
 * assert(ansi::is_enabled() == false);
 *
 * // enable locally (for current thread only)
 * FP_WITH(ansi::use_in_context = true) {
 *     assert(ansi::is_enabled() == true);
 * }
 * // previous state is restored when going out of scope
 * assert(ansi::ansi_enabled() == false);
 * ~~~
 */
bool is_enabled();

//@{
/// See color::enabled().
void enable_globally();
void disable_globally();
extern thread_local context_value<const bool> use_in_context;
//@}

} // namespace fp::util::ansi
