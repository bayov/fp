#pragma once

#include <fp/ast/import.h>
#include <fp/parse/detail/parser_state.h>

namespace fp::parse::detail::parsers {

inline ast::node import(parser_state& s) {
    auto keyword = s.it++;
    std::list<lex::token_iterator> identifiers;
    while (true) {
        if (!s.it_is<lex::token::IDENTIFIER>()) {
            s.error(s.it, s.it, "Expected identifier");
            return ast::make<ast::error>(s.it, s.it + 1);
        }
        identifiers.push_back(s.it++);
        if (!s.it_is<lex::token::SCOPE>()) { break; }
        ++s.it;
    }
    return ast::make<ast::import>(keyword, std::move(identifiers));
}

} // namespace fp::parse::detail::parsers
