#pragma once

#include <variant>

#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/transform.hpp>

#include <fp/util/box.h>

namespace fp::ast {

namespace detail {

#define FP_FORWARD_DECLARE_NODE_CLASS(_1, _2, node_class) class node_class;

#define FP_BOX_NODE_CLASS(_1, _2, node_class) util::box<node_class>

#define FP_AST_NODES_I(node_classes)\
    BOOST_PP_SEQ_FOR_EACH_R(1, FP_FORWARD_DECLARE_NODE_CLASS, _, node_classes)\
    using variant_node = std::variant<BOOST_PP_SEQ_ENUM(\
        BOOST_PP_SEQ_TRANSFORM_S(1, FP_BOX_NODE_CLASS, _, node_classes)\
    )>

#define FP_AST_NODES(node_classes...)\
    FP_AST_NODES_I(BOOST_PP_VARIADIC_TO_SEQ(node_classes))

} // detail

FP_AST_NODES(
    binary_op
);

/// Represents a node in an AST.
struct node : variant_node { using variant_node::variant; };

} // fp::ast
