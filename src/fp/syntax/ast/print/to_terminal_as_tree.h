#pragma once

#include <ostream>

#include <fp/syntax/ast/node.h>

namespace fp::syntax::ast::print {

/**
 * Prints the given AST to the given output-stream in a textual form.
 *
 * If ansi::is_enabled() is true then the AST text will be augmented with ANSI
 * escape codes.
 */
void to_terminal_as_tree(std::ostream&, const node&);

} // namespace fp::syntax::ast::print
