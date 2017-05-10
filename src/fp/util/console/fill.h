#pragma once

#include <string>
#include <string_view>

#include <fp/util/as_string.h>

namespace fp::util::console {

inline std::string fill(
    size_t width,
    const std::string_view& s,
    char fill_char = ' '
) {
    size_t fill_size = width > s.size() ? width - s.size() : 0;
    std::string result(fill_size, fill_char);
    result += s;
    return result;
}

inline std::string fill(
    size_t width,
    const char* s,
    char fill_char = ' '
) {
    return fill(width, std::string_view(s), fill_char);
}

inline std::string fill(
    size_t width,
    const std::string& s,
    char fill_char = ' '
) {
    return fill(width, std::string_view(&s.front(), s.size()), fill_char);
}

template <class T>
std::string fill(size_t width, const T& v, char fill_char = ' ') {
    return fill(width, as_string(v), fill_char);
}

} // namespace fp::util::console
