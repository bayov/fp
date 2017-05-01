#pragma once

#include <stdexcept>
#include <limits>
#include <list>

#include <fp/common/diagnostic.h>

namespace fp {

/// Thrown by @ref diagnostic_report when it reaches the maximum allowed errors.
struct compilation_error : std::exception {
    const char* what() const noexcept override;
};

class diagnostic_report {
public:

    /**
     * Set the maximum amount of error diagnostics allowed before a
     * @ref compilation_error is thrown.
     *
     * By default, there's no limit on the maximum amount of errors allowed.
     */
    void set_max_errors(size_t);

    /// @return A list of accumulated error diagnostics.
    const std::list<diagnostic>& errors() const;

    /// @return A list of accumulated warning diagnostics.
    const std::list<diagnostic>& warnings() const;

    /// Add a diagnostic to the report.
    void add(diagnostic);

private:

    size_t m_max_errors = std::numeric_limits<size_t>::max();
    std::list<diagnostic> m_errors;
    std::list<diagnostic> m_warnings;

};

} // fp