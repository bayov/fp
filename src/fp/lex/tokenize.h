#pragma once

#include <fp/common/input.h>
#include <fp/common/diagnostic_report.h>
#include <fp/lex/token_list.h>

namespace fp::lex {

//@{
/**
 * Tokenize the given input.
 *
 * Stores diagnostic problems in the given @ref diagnostic_report.
 *
 * @throws compilation_error
 *      Thrown by @ref diagnostic_report when reaching the maximum number of
 *      allowed errors.
 */
token_list tokenize(const input&, diagnostic_report&);
token_list tokenize(const input_view&, diagnostic_report&);
//@}

} // fp::lex
