#include <gtest/gtest.h>

#include <fp/lex/tokenize.h>
#include <fp/parse/detail/parser.h>
#include <fp/util/match.h>

namespace fp::parse {

TEST(parse, test) {
    std::string symbols =
R"fp(
a - b - c
)fp";

    auto tokens = lex::tokenize(symbols);
    detail::parser parser;
    ast::node ast = parser.parse(tokens);

    std::function<void(const ast::node&)> print_ast = [&](const ast::node& n) {
        util::match(n)(
            [&](const ast::identifier& id) { std::cout << id.name(); },
            [&](const ast::integer& n) { std::cout << n.value(); },
            [&](const ast::binary_op& op) {
                std::cout << "(";
                print_ast(op.lhs());
                std::cout << " " << op.op_symbols() << " " ;
                print_ast(op.rhs());
                std::cout << ")";
            },
            [&](const ast::prefix_op& op) {
                std::cout << "(";
                std::cout << op.op_symbols();
                print_ast(op.rhs());
                std::cout << ")";
            },
            [&](const ast::postfix_op& op) {
                std::cout << "(";
                print_ast(op.lhs());
                std::cout << op.op_symbols();
                std::cout << ")";
            }
        );
    };

    std::cout << std::endl << "------------------------" << std::endl;
    print_ast(ast);
    std::cout << std::endl << "------------------------" << std::endl;
}

} // fp::lex
