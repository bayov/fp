#include "node.h"

namespace fp::syntax::ast {

lex::tokenized_view node::tokens() const {
    return visit([](const auto& n) { return n.tokens(); });
}

const fp::source_location& node::source_location() const {
    return visit([](const auto& n) -> const auto& {
        return n.source_location();
    });
}

node::node(std::unique_ptr<detail::variant_node> variant_node)
    : variant_node(std::move(variant_node)) {}

} // namespace fp::syntax::ast
