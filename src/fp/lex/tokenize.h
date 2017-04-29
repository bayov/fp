#pragma once

#include <fp/common/types.h>

#include "error.h"
#include "token_list.h"

namespace fp::lex {

//@{
/**
 * @return A list of tokens from the given input symbols.
 *
 * @throws fp::lex::error
 *      On invalid input.
 */
token_list tokenize(const input&);
token_list tokenize(const input_view&);
//@}

} // fp::lex
