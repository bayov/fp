#pragma once

#include <fp/ast/integer.h>
#include <fp/parse/detail/parser_state.h>

namespace fp::parse::detail::parsers {

inline ast::node integer(parser_state& s) {
    return ast::make<ast::integer>(s.it++);
}

} // namespace fp::parse::detail::parsers
