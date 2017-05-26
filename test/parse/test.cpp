#include <gtest/gtest.h>

#include <fp/lex/tokenize.h>
#include <fp/parse/parse.h>
#include <fp/util/match.h>

namespace fp::parse {

TEST(parse, test) {
    input_view symbols =
R"fp(
1 + 2$3
)fp";

    diagnostic_report diagnostics;
    auto tokens = lex::tokenize(symbols, diagnostics);

    ast::node ast = parse(tokens, diagnostics);

    std::string s("hello");
    std::cout << s;
    std::vector<std::string> v;
    v.push_back("hello");
    v.push_back("hello");
    v.push_back("hello");
    v.push_back("hello");
    v.push_back("hello");
    v.push_back("hello");
    v.push_back("hello");

    std::function<void(const ast::node&)> print_ast = [&](const ast::node& n) {
        n.match(
            [&](const ast::error&) { std::cout << "ERROR"; },
            [&](const ast::empty&) { std::cout << "EMPTY"; },
            [&](const ast::identifier& id) { std::cout << id.name(); },
            [&](const ast::integer& i) { std::cout << i.value(); },
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
    std::cout << diagnostics << std::endl;
}

} // namespace fp::lex
