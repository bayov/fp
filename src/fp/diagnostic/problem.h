#pragma once

#include <string>
#include <vector>

#include <fp/source_code.h>

namespace fp::diagnostic {

/// The severity of a diagnostic::problem.
enum class severity { WARNING, ERROR };

/// @see diagnostic::location.
enum class location_kind { PRIMARY, SUPPLEMENT };

/**
 * A source code location that is relevant to a reported diagnostic::problem.
 *
 * A location of kind `PRIMARY` is the primary location of the problem (or one
 * of several such), while a `SUPPLEMENT` is a relevant addition.
 */
struct location {
    location_kind       kind;
    fp::source_location source_location;
    std::string         text;
};

/**
 * Information about a single problem encountered by the compiler, during any
 * stage of the compilation.
 */
struct problem {
    diagnostic::severity severity() const { return severity_; }

    /// Returns a textual description of the problem.
    const std::string& text() const { return text_; }

    /// Returns a list of relevant source locations.
    const std::vector<location>& locations() const { return locations_; }

    /// Add a primary source location.
    problem& add_primary(fp::source_location source, std::string text = "");

    /// Add a supplemental source location.
    problem& add_supplement(fp::source_location source, std::string text = "");

private:
    diagnostic::severity  severity_;
    std::string           text_;
    std::vector<location> locations_;

    problem(diagnostic::severity, std::string text);

    friend problem warning(std::string text);
    friend problem error  (std::string text);
};

/// Construct a diagnostic::error with severity::WARNING.
problem warning(std::string text);

/// Construct a diagnostic::error with severity::ERROR.
problem error(std::string text);

} // namespace fp::diagnostic
