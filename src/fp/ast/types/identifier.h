#pragma once

#include <fp/ast/detail/base_node.h>

namespace fp::ast {

struct identifier : detail::base_node {
    source_view chars;

    identifier(lex::token_iterator identifier_token_it) :
        base_node(identifier_token_it, identifier_token_it + 1),
        chars(identifier_token_it->get_attribute<lex::token::IDENTIFIER>())
    {}
};

} // namespace fp::ast
