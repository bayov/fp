#include "node.h"

namespace fp::ast {

namespace detail {

const base_node& base(const node& n) {
    return std::visit(
        [](const auto& v) -> const base_node& { return (const base_node&)(v); },
        *n
    );
}

} // namespace detail

const source_location& source(const node& n) { return base(n).source(); }

const lex::token_view& tokens(const node& n) { return base(n).tokens(); }

} // namespace fp::ast
