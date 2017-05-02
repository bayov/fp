#pragma once

#include <string>
#include <optional>
#include <list>

#include <fp/util/enum_class.h>
#include <fp/common/source_location.h>

namespace fp {

/// The severity of a @ref diagnostic.
ENUM_CLASS(severity, uint8_t, ERROR, WARNING);

/// Information about a single problem encountered by the compiler.
class diagnostic {
public:

    /// A relevant source location, with optional text.
    NAMED_TUPLE(supplement, (source_location, source)(std::string, text));

    /// A correlated note, with optional source-location.
    NAMED_TUPLE(
        note,
        (std::string, text)(std::optional<source_location>, source)
    );

    /// A suggestion to fix the problem: replace `source` with `replacement`.
    NAMED_TUPLE(fix_suggestion, (source_location, source)(input, replacement));

    /// Construct an error diagnostic.
    static diagnostic error(source_location, std::string text);

    /// Construct a warning diagnostic.
    static diagnostic warning(source_location, std::string text);

    /// @return The severity of the problem.
    fp::severity severity() const;

    /// @return The source-location of the problem.
    const source_location& source() const;

    /// @return A description of the problem.
    const std::string& text() const;

    /// @return Supplementary source locations.
    const std::list<supplement>& supplements() const;

    /// @return Extra notes.
    const std::list<note>& notes() const;

    /// @return Suggestions for fixing the problem.
    const std::list<fix_suggestion>& fix_suggestions() const;

    /// Add a source supplement to the diagnostic.
    void add_supplement(source_location source, std::string text = "");

    /// Add a note to the diagnostic.
    void add_note(std::string text);

    /// Add a note to the diagnostic, with an associated source-location.
    void add_note(std::string text, source_location);

    /// Add a suggestion for a fix (by `replacement` of `source_location`).
    void add_fix_suggestion(source_location, input replacement);

private:

    fp::severity m_severity;
    source_location m_source;
    std::string m_text;
    std::list<supplement> m_source_supplements;
    std::list<note> m_notes;
    std::list<fix_suggestion> m_fix_suggestions;

    diagnostic(
        fp::severity severity,
        source_location source,
        std::string text
    );

};

} // namespace fp
