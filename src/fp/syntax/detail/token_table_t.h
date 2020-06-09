#pragma once

#include <fp/util/table.h>
#include <fp/lex/token.h>

namespace fp::syntax::detail {

template <class Value>
using token_table_t = util::table<lex::token, Value, lex::n_tokens>;

} // namespace fp::syntax::detail
