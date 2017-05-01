#pragma once

#include <fp/common/input.h>
#include <fp/common/diagnostic_report.h>
#include <fp/lex/token_list.h>

namespace fp::lex {

/**
 * Tokenize the given input.
 *
 * When encountering an error, a diagnostic will be reported and an error token
 * will be added to the result.
 *
 * @throws compilation_error
 *      Thrown when the maximum allowed errors is reached (as set by the given
 *      @ref diagnostic_report).
 */
token_list tokenize(const input_view&, diagnostic_report&);

} // fp::lex
