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
        print_node_name("binary_op", default_color, op);
        print_children(binary_op.lhs, binary_op.rhs);
    }

    void print(const ast::empty& error) {
        os << default_color << "empty AST";
    }

    void print(const ast::error& error) {
        os << red << "error";
        if (!error.tokens().empty()) {
            os << default_color << ": ";
            bool first = true;
            for (const auto& t : error.tokens()) {
                if (!first) { os << ", "; }
                first = false;
                os << default_color << "token::";
                lex::print::to_terminal(os, t);
            }
        }
        os << '\n';
    }

    void print(const ast::identifier& identifier) {
        print_node_name("identifier", magenta, identifier.chars);
    }

    void print(const ast::infix_error& infix_error) {
        os << red << "infix_error";
        os << default_color << ": token::";
        lex::print::to_terminal(os, infix_error.invalid_infix_token);
        os << '\n';
        print_children(infix_error.lhs);
    }

    void print(const ast::number& number) {
        print_node_name("number", blue, number.chars);
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

    void print_node_name(
        const std::string_view& name,
        graphics_code color,
        std::string_view extra = ""
    ) {
        os << color << name;
        if (!extra.empty()) { os << grey << " (" << extra << ')'; }
        os << '\n';
    }

    struct annotated_child {
        std::string_view annotation;
        const ast::node& node;

        annotated_child(const ast::node& node) : annotation(""), node(node) {}

        annotated_child(std::string_view annotation, const ast::node& node)
            : annotation(annotation), node(node) {}
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
};

void to_terminal(std::ostream& os, const ast::node& node) {
    node.visit(Visitor(os));
    os << reset;
}

} // namespace fp::syntax::ast::print
