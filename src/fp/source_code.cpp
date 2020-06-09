#include "source_code.h"

namespace fp {

source_file::source_file(std::string name, std::string content) :
    name(std::move(name)), content_data(std::move(content))
{
    content = content_data;
}

source_file::source_file(std::string name, std::string_view content) :
    name(std::move(name)), content(content)
{}

source_file::source_file(std::string name, const char* content) :
    name(std::move(name)), content(content)
{}

source_location source_location::slice(source_iterator first) const {
    return slice(first, chars.end());
}

source_location source_location::slice(
    source_iterator first,
    source_iterator last
) const {
    source_location result = *this;
    // find the beginning of the slice's line
    for (auto it = chars.begin(); it < first; ++it) {
        bool is_newline = false;
        if (*it == '\n') { is_newline = true; }
        if (*it == '\r') {
            is_newline = true;
            if (it + 1 < first && *it == '\n') { ++it; } // goddamn CRLF
        }
        if (is_newline) {
            result.line = it + 1;
            ++result.line_number;
        }
    }
    result.chars = make_source_view(first, last);
    return result;
}

source_location source_location::slice_end() const {
    return slice(chars.end());
}

} // namespace fp
