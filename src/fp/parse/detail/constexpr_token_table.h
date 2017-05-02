#pragma once

#include <fp/util/constexpr_table.h>
#include <fp/lex/token.h>

namespace fp::parse::detail {

template <class Value>
using constexpr_token_table = util::constexpr_table<
    lex::token,
    Value,
    util::enum_class<lex::token>::size
>;

} // namespace fp::parse::detail
