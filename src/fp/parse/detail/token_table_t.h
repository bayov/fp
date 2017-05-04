#pragma once

#include <fp/util/table.h>
#include <fp/lex/token.h>

namespace fp::parse::detail {

template <class Value>
using token_table_t = util::table<
    lex::token,
    Value,
    util::enum_class<lex::token>::size
>;

} // namespace fp::parse::detail
