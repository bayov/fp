#pragma once

#include "base_node.h"

namespace fp::ast {

class identifier : public base_node {
public:

    explicit identifier(lex::token_iterator it) : base_node(it, it + 1) {}

    const input_view& name() const {
        return tokens().front().attribute.as<lex::token::IDENTIFIER>();
    }

};

} // fp::ast
