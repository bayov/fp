#include "diagnostic.h"

namespace fp {

diagnostic diagnostic::error(source_location source, std::string text) {
    return diagnostic(severity::ERROR, std::move(source), std::move(text));
}

diagnostic diagnostic::warning(source_location source, std::string text) {
    return diagnostic(severity::WARNING, std::move(source), std::move(text));
}

fp::severity diagnostic::severity() const { return m_severity; }

const source_location& diagnostic::source() const { return m_source; }

const std::string& diagnostic::text() const { return m_text; }

auto diagnostic::supplements() const -> const std::list<supplement>& {
    return m_source_supplements;
}

auto diagnostic::notes() const -> const std::list<note>& { return m_notes; }

auto diagnostic::fix_suggestions() const -> const std::list<fix_suggestion>& {
    return m_fix_suggestions;
}

void diagnostic::add_supplement(source_location source, std::string text) {
    m_source_supplements.emplace_back(std::move(source), std::move(text));
}

void diagnostic::add_note(std::string text) {
    m_notes.emplace_back(std::move(text), std::optional<source_location>{});
}

void diagnostic::add_note(std::string text, source_location source) {
    m_notes.emplace_back(std::move(text), std::move(source));
}

void diagnostic::add_fix_suggestion(source_location source, input replacement) {
    m_fix_suggestions.emplace_back(std::move(source), std::move(replacement));
}

diagnostic::diagnostic(
    fp::severity severity,
    source_location source,
    std::string text
) :
    m_severity(severity),
    m_source(std::move(source)),
    m_text(std::move(text))
{}

} // namespace fp
