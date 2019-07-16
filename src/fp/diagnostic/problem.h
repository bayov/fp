#pragma once

#include <string>
#include <optional>
#include <list>

#include <fp/util/record.h>
#include <fp/source_code.h>

namespace fp::diagnostic {

/// The severity of a diagnostic::problem.
enum class severity { WARNING, ERROR };

/**
 * A supplementary source code section that is relevant to a reported
 * diagnostic::problem.
 */
FP_RECORD(supplement,
    (fp::source_location, source_location)
    (std::string, text)
);

/**
 * An additional note about a diagnostic::problem that might help clarify its
 * nature. Can optionally refer to the source code.
 */
FP_RECORD(note,
    (std::string, text)
    (std::optional<fp::source_location>, source_location)
);

/**
 * A suggestion for a possible fix to a diagnostic::problem. The suggestion
 * format is to replace the contents of `source_location` with `replacement`.
 */
FP_RECORD(fix_suggestion,
    (fp::source_location, source_location)
    (fp::source_code    , replacement    )
);

/**
 * Information about a single problem encountered by the compiler, during any
 * stage of the compilation.
 */
struct problem {
    diagnostic::severity severity() const { return severity_; }

    /// Returns the source location from which the problem originated.
    const fp::source_location& source_location() const {
        return source_location_;
    }

    /// Returns a textual description of the problem.
    const std::string& text() const { return text_; }

    /// Returns additional source locations relevant to the problem.
    const std::list<supplement>& supplements() const { return supplements_; }

    /// Returns (hopefully) helpful notes to clarify what the problem.
    const std::list<note>& notes() const { return notes_; }

    /// Returns suggestions for possible fixes to the problem.
    const std::list<fix_suggestion>& fix_suggestions() const {
        return fix_suggestions_;
    }

    /// Add a supplemental source location.
    void add_supplement(fp::source_location source, std::string text = "");

    /// Add a note, without referring to any source code location.
    void add_note(std::string text);

    /// Add a note with a reference to a source location.
    void add_note(std::string text, fp::source_location);

    /**
     * Add a suggestion for a possible fix.
     *
     * The format is a suggestion to replace the given `source_location` with
     * the code given in `replacement`.
     */
    void add_fix_suggestion(fp::source_location, source_code replacement);

private:
    diagnostic::severity      severity_;
    fp::source_location       source_location_;
    std::string               text_;
    std::list<supplement>     supplements_;
    std::list<note>           notes_;
    std::list<fix_suggestion> fix_suggestions_;

    problem(diagnostic::severity, fp::source_location, std::string text);

    friend problem warning(fp::source_location, std::string text);
    friend problem error  (fp::source_location, std::string text);
};

/// Construct a diagnostic::error with severity::WARNING.
problem warning(source_location, std::string text);

/// Construct a diagnostic::error with severity::ERROR.
problem error(source_location, std::string text);

///**
// * If std::ostream is std::cout, std::cerr, or std::clog, the diagnostic will be
// * printed with colors (ANSI escape codes).
// *
// * To disable colors, you can use fp::util::color::disable_in_scope.
// */
//std::ostream& operator<<(std::ostream&, const problem&);

} // namespace fp::diagnostic
