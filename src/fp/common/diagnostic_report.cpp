#include "diagnostic_report.h"

namespace fp {

const char* compilation_error::what() const noexcept {
    return "Compilation error (see diagnostics report for details)";
}

void diagnostic_report::set_max_errors(size_t n) { m_max_errors = n; }

const std::list<diagnostic>& diagnostic_report::errors() const {
    return m_errors;
}

const std::list<diagnostic>& diagnostic_report::warnings() const {
    return m_warnings;
}

void diagnostic_report::report(diagnostic d) {
    auto& list = d.severity() == severity::ERROR ? m_errors : m_warnings;
    list.push_back(std::move(d));
    if (m_errors.size() >= m_max_errors) { throw compilation_error(); }
}

void diagnostic_report::report_error(source_location source, std::string text) {
    report(diagnostic::error(std::move(source), std::move(text)));
}

void diagnostic_report::report_warning(source_location source, std::string text) {
    report(diagnostic::warning(std::move(source), std::move(text)));
}

} // fp
