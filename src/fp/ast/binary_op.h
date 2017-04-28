#pragma once

#include <unordered_map>

#include <fp/util/enum_class.h>

#include <fp/lex/binary_ops.h>

#include "node.h"

namespace fp::ast {

#define FP_BINARY_OP_ENUMERATOR(enumerator, _) enumerator

ENUM_CLASS(binary, uint8_t, FP_BINARY_OPS_ENUM(FP_BINARY_OP_ENUMERATOR));

namespace detail {

#define FP_BINARY_OP_MAP_ITEM(enumerator, op)\
    { binary::enumerator, op },

/// A mapping from binary-ops to their string representation.
inline std::unordered_map<binary, std::string_view> create_binary_ops_map() {
    return { FP_BINARY_OPS_FOR_EACH(FP_BINARY_OP_MAP_ITEM) };
}

} // detail

/// @return The given binary-op's string representation.
inline std::string_view as_string(binary op) {
    static const auto keywords_map = detail::create_binary_ops_map();
    return keywords_map.at(op);
}

class binary_op : public node {
public:

    binary op() const { return m_op; }
    const node& lhs() const { return m_lhs; }
    const node& rhs() const { return m_rhs; }

private:

    node m_lhs;
    node m_rhs;
    binary m_op;

};

} // fp::ast
