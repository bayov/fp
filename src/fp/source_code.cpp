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

} // namespace fp
