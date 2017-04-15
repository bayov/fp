#pragma once

#include <string>
#include <sstream>

namespace fp::util {

/// @return The result of ostream-ing the given value.
template <class T>
std::string as_string(const T& v) {
    std::ostringstream oss;
    oss << v;
    return oss.str();
}

} // fp::util
