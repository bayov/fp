#pragma once

#include <string>
#include <sstream>

namespace fp::util {

template <class Range>
std::string join(const Range& r, std::string_view sep = ", ") {
    auto it = std::begin(r);
    auto end = std::end(r);
    if (it == end) { return ""; }
    std::ostringstream oss;
    oss << *it++;
    for (; it != end; ++it) { oss << sep << *it; }
    return oss.str();
}

} // namespace fp::util
