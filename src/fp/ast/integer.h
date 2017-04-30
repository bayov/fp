#pragma once

#include <fp/ast/base_node.h>

namespace fp::ast {

class integer : public base_node {
public:

    explicit integer(lex::token_iterator it) : base_node(it, it + 1) {}

    integer_type value() const {
        return tokens().front().attribute.as<lex::token::INTEGER>();
    }

};

} // fp::ast
