#pragma once

#include <fp/source_code.h>
#include <fp/diagnostic/report.h>
#include <fp/lex/tokenized_list.h>

namespace fp::lex {

/**
 * Tokenize the given source code.
 *
 * All encountered problems during tokenization will be reported to the given
 * diagnostic::report.
 *
 * @throws fp::compilation_error
 *     Thrown when the maximum number of allowed errors is reached (as set by
 *     the given diagnostic::report).
 */
tokenized_list tokenize(source_view, diagnostic::report&);

} // namespace fp::lex
