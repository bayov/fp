#pragma once

#include <fp/util/with.h>
#include <fp/ast/node.h>
#include <fp/parse/detail/parser_state.h>
#include <fp/parse/detail/token_table_t.h>
#include <fp/parse/detail/parsers/identifier.h>
#include <fp/parse/detail/parsers/integer.h>
#include <fp/parse/detail/parsers/import.h>
#include <fp/parse/detail/parsers/prefix_op.h>

namespace fp::parse::detail {

using prefix_parser_t = ast::node (*)(parser_state&);

inline ast::node prefix_parser_error(parser_state& s) {
    s.error();
    ++s.it;
    return ast::make<ast::error>(s.it - 1, s.it);
}

inline ast::node prefix_parser_skip_error(parser_state& s) {
    ++s.it;
    return ast::make<ast::error>(s.it - 1, s.it);
}

constexpr auto prefix_parser_table = ([]() {
    auto t = token_table_t<prefix_parser_t>::with_default(prefix_parser_error);

    // identifiers and literals
    t[lex::token::IDENTIFIER] = parsers::identifier;
    t[lex::token::INTEGER] = parsers::integer;

    // language constructs
    t[lex::token::IMPORT] = parsers::import;

    // prefix-operators
    t[lex::token::DECORATOR] = parsers::prefix_op;
    t[lex::token::BIT_NOT] = parsers::prefix_op;
    t[lex::token::PLUS] = parsers::prefix_op;
    t[lex::token::MINUS] = parsers::prefix_op;
    t[lex::token::BIT_AND] = parsers::prefix_op;
    t[lex::token::INC] = parsers::prefix_op;
    t[lex::token::DEC] = parsers::prefix_op;

    // error
    t[lex::token::ERROR] = prefix_parser_skip_error;

    return t;
})();

ast::node parse_prefix(parser_state& s) {
    ast::node node = prefix_parser_table[s.it->value](s);
    if (node.is<ast::error>()) {
        // try to recover from the error by parsing until succeeding, while
        // ignoring all errors along the way to avoid diagnostics clutter
        WITH(s.ignore_diagnostics_in_scope()) {
            while (
                s.it != s.end &&
                prefix_parser_table[s.it->value](s).is<ast::error>()
            ) {}
        }
    }
    return node;
}

} // namespace fp::parse::detail
