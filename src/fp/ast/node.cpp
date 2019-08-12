#include "node.h"

namespace fp::ast {

const fp::source_location& node::source_location() const {
    return get_base_node().source_location;
}

const lex::tokenized_view& node::tokens() const {
    return get_base_node().tokens;
}

const detail::base_node& node::get_base_node() const {
    return visit([](const detail::base_node& base_node) -> const auto& {
        return base_node;
    });
}

} // namespace fp::ast
