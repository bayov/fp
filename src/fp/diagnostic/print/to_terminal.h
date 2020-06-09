#pragma once

#include <ostream>

#include <fp/diagnostic/report.h>

namespace fp::diagnostic::print {

//@{
/**
 * Prints the given diagnostic::problem or diagnostic::report to the given
 * output-stream in a textual form.
 *
 * If ansi::is_enabled() is true then the report will be augmented with ANSI
 * escape codes.
 */
void to_terminal(std::ostream&, const diagnostic::problem&);
void to_terminal(std::ostream&, const diagnostic::report&);
//@}

} // namespace fp::diagnostic::print
