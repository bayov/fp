#pragma once

#include <stdexcept>
#include <limits>
#include <list>

#include <fp/compilation_error.h>
#include <fp/diagnostic/problem.h>

namespace fp::diagnostic {

struct report {
    /**
     * Sets the maximum amount of diagnostic::error allowed before a
     * fp::compilation_error is thrown.
     *
     * By default, there's no limit on the maximum amount of errors allowed,
     * and errors will keep accumulating without exceptions being thrown.
     */
    void set_max_errors(size_t n) { max_errors_ = n; }

    //@{
    /// Returns the list of accumulated warnings.
          std::list<problem>& warnings()       { return warnings_; }
    const std::list<problem>& warnings() const { return warnings_; }
    //@}

    //@{
    /// Returns the list of accumulated errors.
          std::list<problem>& errors()       { return errors_; }
    const std::list<problem>& errors() const { return errors_; }
    //@}

    /**
     * Append a new diagnostic::problem to the report.
     *
     * @throws fp::compilation_error
     *     When the problem has severity::ERROR, and the current error count had
     *     reached the maximum number of errors allowed (as set by
     *     report::set_max_errors).
     */
    void add(problem);

private:
    size_t max_errors_ = std::numeric_limits<size_t>::max();
    std::list<problem> errors_;
    std::list<problem> warnings_;
};

///**
// * If std::ostream is std::cout, std::cerr, or std::clog, the diagnostics will
// * be printed with colors (ANSI escape codes).
// *
// * To disable colors, you can use fp::util::color::disable_in_scope.
// */
//std::ostream& operator<<(std::ostream&, const report&);

} // namespace fp::diagnostic
