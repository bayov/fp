#include <fp/util/context_value.h>
#include <fp/util/with.h>
#include <fp/util/ansi/codes.h>
#include <fp/util/type_name.h>
#include <fp/lex/print/to_terminal.h>

#include "to_terminal.h"

namespace fp::syntax::ast::print {

using namespace util::ansi;

struct Visitor {
    std::ostream& os;
    explicit Visitor(std::ostream& os) : os(os) {}

    /* The code could be cleaner if every `print` method was changed to
     * `operator()` and this method was removed, but having this extra layer
     * makes error-reporting when missing an overload for AST types prettier.
     */
    template <class Node>
    void operator()(const Node& node) { print(node); }

    void print(const ast::binary_op& binary_op) {
        std::string_view op = binary_op.op_source_location().chars;
        print_node_line(binary_op, default_color, op);
        print_children(binary_op.lhs, binary_op.rhs);
    }

    void print(const ast::char_& char_) {
        print_node_line(char_, green, char_.source_location().chars);
    }

    void print(const ast::empty& error) {
        os << default_color << "ast::empty";
    }

    void print(const ast::error& error) {
        os << red << "ast::error";
        if (!error.tokens().empty()) {
            os << default_color << ": ";
            bool first = true;
            for (const auto& t : error.tokens()) {
                if (!first) { os << ", "; }
                first = false;
                lex::print::to_terminal(os, t);
            }
        }
        os << '\n';
    }

    void print(const ast::identifier& identifier) {
        print_node_line(identifier, magenta, identifier.chars);
    }

    void print(const ast::if_& if_) {
        os << yellow << "ast::if\n";
        print_children(
            annotated_child { "condition", if_.condition },
            annotated_child { "body", if_.body }
        );
    }

    void print(const ast::infix_error& infix_error) {
        os << red << "ast::infix_error";
        os << default_color << ": ";
        lex::print::to_terminal(os, infix_error.invalid_infix_token);
        os << '\n';
        print_children(infix_error.lhs);
    }

    void print(const ast::number& number) {
        print_node_line(number, blue, number.chars);
    }

    void print(const ast::postfix_op& postfix_op) {
        std::string_view op = postfix_op.op_source_location().chars;
        print_node_line(postfix_op, default_color, op);
        print_children(postfix_op.lhs);
    }

    void print(const ast::prefix_op& prefix_op) {
        std::string_view op = prefix_op.op_source_location().chars;
        print_node_line(prefix_op, default_color, op);
        print_children(prefix_op.rhs);
    }

    void print(const ast::sequence& sequence) {
        std::string_view separator =
            sequence.separators.front()->source_location.chars;
        print_node_line(sequence, default_color, separator);
        print_children_range(sequence.nodes);
    }

private:
    enum class child_context {
        YET_TO_BE_PRINTED,
        ALREADY_PRINTED,
        LAST_AND_YET_TO_BE_PRINTED,
        LAST_AND_ALREADY_PRINTED
    };
    util::context_value<child_context> child_contexts;
    void spaces_prefix            () { os << grey << "    "; }
    void vertical_prefix          () { os << grey << "│   "; }
    void vertical_and_right_prefix() { os << grey << "├── "; }
    void up_and_right_prefix      () { os << grey << "└── "; }

    void print_prefixes() {
        for (child_context& ctx : child_contexts) {
            switch (ctx) {
                case child_context::YET_TO_BE_PRINTED:
                    vertical_and_right_prefix();
                    ctx = child_context::ALREADY_PRINTED;
                    break;
                case child_context::ALREADY_PRINTED:
                    vertical_prefix();
                    break;
                case child_context::LAST_AND_YET_TO_BE_PRINTED:
                    up_and_right_prefix();
                    ctx = child_context::LAST_AND_ALREADY_PRINTED;
                    break;
                case child_context::LAST_AND_ALREADY_PRINTED:
                    spaces_prefix();
                    break;
            }
        }
    }

    template <class Node>
    void print_node_line(
        const Node& node,
        graphics_code color,
        std::string_view extra = ""
    ) {
        os << color << extra;
        std::string_view node_name =
            util::type_name<Node>.substr(sizeof("fp::syntax::") - 1);
        if (!extra.empty()) { os << grey << " (" << node_name << ')'; }
        os << '\n';
    }

    struct annotated_child {
        std::string_view annotation;
        const ast::node& node;
    };

    template <class Child, class... Childs>
    void print_children(const Child& child, const Childs&... children) {
        FP_WITH(
            child_contexts =
                sizeof...(children) == 0 ?
                child_context::LAST_AND_YET_TO_BE_PRINTED :
                child_context::YET_TO_BE_PRINTED
        ) {
            print_prefixes();
            if constexpr (std::is_same_v<Child, annotated_child>) {
                os << default_color << child.annotation << ": ";
                child.node.visit(*this);
            } else {
                child.visit(*this);
            }
        }
        if constexpr (sizeof...(children) > 0) { print_children(children...); }
    }

    void print_children_range(const std::vector<ast::node>& children) {
        for (const auto& child : children) {
            FP_WITH(
                child_contexts =
                    &child == &children.back() ?
                    child_context::LAST_AND_YET_TO_BE_PRINTED :
                    child_context::YET_TO_BE_PRINTED
            ) {
                print_prefixes();
                child.visit(*this);
            }
        }
    }
};

void to_terminal(std::ostream& os, const ast::node& node) {
    node.visit(Visitor(os));
    os << reset;
}

} // namespace fp::syntax::ast::print
