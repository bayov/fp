#pragma once

#include <fp/lex/tokenized_list.h>
#include <fp/diagnostic/report.h>
#include <fp/syntax/ast/node.h>

namespace fp::syntax {

/**
 * Constructs an AST from the given list of tokens.
 *
 * All encountered problems during syntax parsing will be reported to the given
 * diagnostic::report.
 *
 * @throws fp::compilation_error
 *     Thrown when the maximum number of allowed errors is reached (as set by
 *     the given diagnostic::report).
 */
ast::node parse(lex::tokenized_view, diagnostic::report&);

} // namespace fp::syntax
