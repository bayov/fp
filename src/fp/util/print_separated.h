#pragma once

#include <iostream>
#include <string_view>

namespace fp::util {

/// Prints the given values separated by the given separator.
template <class... Ts>
void print_separated(
    std::string_view separator, std::ostream& os, const Ts&... vs
) {
    bool first = true;
    (..., [&]() {
        if (!first) { os << separator; }
        first = false;
        os << vs;
    }());
}

/// Prints the given values separated with a comma (", ").
template <class... Ts>
void print_comma_separated(std::ostream& os, const Ts&... vs) {
    print_separated(", ", os, vs...);
}

} // namespace fp::util
