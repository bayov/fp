#pragma once

#include <csignal>
#include <cstdlib>
#include <string_view>
#include <sstream>

/**
 * Asserts that the given `condition` is true, and aborts the program otherwise.
 *
 * `message` is a description of the `condition` that must be satisfied, and is
 * given as the RHS to an output stream. Example:
 * ~~~{.cpp}
 * FP_ASSERT(
 *     list.size() == 42,
 *     "`list` should contain 42 items, but has " << list.size() << " items"
 * );
 * ~~~
 *
 * The program is aborted by raising a SIGTRAP signal, which means that in case
 * a debugger is attached to the process, it'll stop on the failed assertion.
 */
#define FP_ASSERT(condition, message...) do {\
    if (!(condition)) {\
        ::fp::util::detail::assert::failure_message << message;\
        ::fp::util::detail::assert::failed_condition = #condition;\
        ::fp::util::detail::assert::file = __FILE__;\
        ::fp::util::detail::assert::line = __LINE__;\
        std::signal(SIGTRAP, ::fp::util::detail::assert::sigtrap_handler);\
        std::raise(SIGTRAP);\
    }\
} while (false)

namespace fp::util::detail::assert {

// filled before calling SIGTRAP handler
extern std::ostringstream failure_message;
extern std::string_view failed_condition;
extern std::string_view file;
extern size_t line;

void sigtrap_handler(int);

} // namespace fp::util::detail::assert
