#pragma once

#include <string>
#include <sstream>

namespace fp::util {

/// The result of ostream-ing the given value.
template <class T>
std::string to_string(const T& v) {
    std::ostringstream oss;
    oss << v;
    // this is a bit inefficient because we're copying the created string's
    // memory from the ostringstream, instead of just stealing it. It can't be
    // easily avoided without ugly measures, so it is left as is for now...
    return oss.str();
}

} // namespace fp::util
