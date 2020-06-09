#pragma once

#include <stdexcept>

namespace fp {

/// Oh no
struct compilation_error : std::exception {
    const char* what() const noexcept override {
        // TODO: maybe diagnostic::report should write something here
        return "Compilation error (see diagnostic report for details)";
    }
};

} // namespace fp
