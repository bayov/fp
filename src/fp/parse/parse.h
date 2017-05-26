#pragma once

#include <fp/common/diagnostic_report.h>
#include <fp/lex/token_view.h>
#include <fp/ast/node.h>

namespace fp::parse {

/**
 * Construct an AST from the given list of tokens.
 *
 * When encountering an error, a diagnostic will be reported and an error node
 * will be added to syntax tree.
 *
 * @throws compilation_error
 *      Thrown when the maximum allowed errors is reached (as set by the given
 *      @ref diagnostic_report).
 */
ast::node parse(const lex::token_view&, diagnostic_report&);

} // namespace fp::parse
