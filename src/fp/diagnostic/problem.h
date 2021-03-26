#pragma once

#include <optional>
#include <string>
#include <vector>

#include <fp/error_codes.h>
#include <fp/source_code.h>

namespace fp::diagnostic {

/// The severity of a diagnostic::problem.
enum class severity { WARNING, ERROR };

/// @see diagnostic::location.
enum class location_kind { PRIMARY, SUPPLEMENT, CONTEXTUAL };

/**
 * A source code location that is relevant to a reported diagnostic::problem.
 *
 * A location of kind `PRIMARY` is the primary location of the problem (or one
 * of several such), while a `SUPPLEMENT` is a relevant addition.
 *
 * `CONTEXTUAL` locations are simply pieces of code that can provide additional
 * context when printed alongside other locations. They are not labeled in any
 * special way (and their `text` is always empty).
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
    std::string_view text() const {
        return error_code_ ? error_code_->brief : text_;
    }

    /// Returns a list of relevant source locations.
    const std::vector<location>& locations() const { return locations_; }

    /**
     * Returns the relevant error::code of the problem if available.
     *
     * If no error::code is available, returns `null`.
     */
     const error::code* error_code() const { return error_code_; }

    /// Add a primary source location.
    problem& add_primary(fp::source_location, std::string text = "");

    /// Add a supplemental source location.
    problem& add_supplement(fp::source_location, std::string text = "");

    /// Add a contextual source location.
    problem& add_contextual(fp::source_location);

private:
    diagnostic::severity  severity_;
    const error::code*    error_code_ = nullptr;
    std::string           text_;
    std::vector<location> locations_;

    problem(diagnostic::severity, const error::code*);
    problem(diagnostic::severity, std::string text);

    friend problem warning(std::string text);
    friend problem error(const error::code*);
    friend problem error(std::string text);
};

/// Construct a diagnostic::error with severity::WARNING.
problem warning(std::string text);

/// Construct a diagnostic::error with severity::ERROR from an error::code.
problem error(const error::code*);

/**
 * Construct a diagnostic::error with severity::ERROR.
 *
 * Avoid constructing errors without an error::code if possible.
 */
problem error(std::string text);

} // namespace fp::diagnostic
