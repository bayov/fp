#pragma once

#include <ostream>

#include <fp/lex/tokenized_list.h>

namespace fp::lex::print {

//@{
/**
 * Prints the given token/s to the given output-stream in a textual form.
 *
 * If ansi::is_enabled() is true then the token/s will be augmented with ANSI
 * escape codes.
 */
void to_terminal(std::ostream&, const token&);
void to_terminal(std::ostream&, const tokenized_token&);
void to_terminal(std::ostream&, const tokenized_list&);
//@}

} // namespace fp::lex::print
