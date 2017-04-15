#pragma once

#include "error.h"
#include "symbol.h"
#include "token_list.h"

namespace fp::lex {

//@{
/**
 * @return A list of tokens from the given input symbols.
 *
 * @throws fp::lex::error
 *      On invalid input.
 */
token_list tokenize(const input_t&);
token_list tokenize(const input_view_t&);
//@}

} // fp::lex
