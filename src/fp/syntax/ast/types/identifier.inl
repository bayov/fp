#pragma once

#include <fp/syntax/ast/detail/base_node.h>

namespace fp::syntax::ast {

struct identifier : detail::base_node<identifier> {
    source_view chars;

    identifier(lex::token_iterator identifier_token_it) :
        base_node(identifier_token_it, identifier_token_it + 1),
        chars(identifier_token_it->get_attribute<lex::token::IDENTIFIER>())
    {}
};

} // namespace fp::syntax::ast
