#include "node.h"

namespace fp::ast {

const base_node& node::as_base() const {
    return visit([](const auto& n) -> const base_node& {
        return (const base_node&)(n);
    });
}

const source_location& node::source() const { return as_base().source(); }

const lex::token_view& node::tokens() const { return as_base().tokens(); }

} // namespace fp::ast
