#pragma once

/**
 * Just a bit of nice syntax-sugar over RAII-style mechanisms.
 *
 * ~~~{.cpp}
 * WITH(std::lock_guard<std::mutex>(my_mutex)) {
 *     // ...
 * } // lock_guard destructed here, unlocking mutex
 * ~~~
 */
#define FP_WITH(value)\
    if ([[maybe_unused]] auto with_value__ = (value); true)
