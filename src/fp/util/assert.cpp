#include <iostream>

#include <fp/util/ansi/codes.h>

#include "assert.h"

namespace fp::util::detail::assert {

std::ostringstream failure_message;
std::string_view failed_condition;
std::string_view file;
size_t line;

void sigtrap_handler(int) {
    using namespace fp::util::ansi;
    std::cerr << bold << red << "assertion failed:" << reset;
    if (failure_message) {
        std::cerr << " " <<  failure_message.str() << reset;
    }
    std::cerr << '\n';
    std::cerr << italic << blue << file << ":" << line << reset << '\n';
    std::cerr << grey << "  |\n";
    std::cerr << grey << "  | " << reset << failed_condition << '\n';
    std::cerr << grey << "  |" << std::endl;
    std::abort();
}

} // namespace fp::util::detail::assert
