#include <cxxabi.h>
#include <memory>

#include "type_name.h"

namespace fp::util {

std::string demangle(const char* name) {
    int status;
    std::unique_ptr<char, decltype(&std::free)> result(
        abi::__cxa_demangle(name, nullptr, nullptr, &status),
        std::free
    );
    switch (status) {
        case 0:
            return result.get();
        case -1:
            throw std::bad_alloc();
        case -2:
            throw std::invalid_argument(
                '"' + std::string(name) + "\" is not a valid mangled name"
            );
        default:
            throw std::runtime_error(
                "abi::__cxa_demangle returned invalid status: " +
                std::to_string(status)
            );
    }
}

} // namespace fp::util
