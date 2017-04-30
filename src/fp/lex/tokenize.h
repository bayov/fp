#pragma once

#include <fp/common/input.h>
#include <fp/lex/token_list.h>

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
