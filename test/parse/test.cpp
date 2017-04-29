#include <gtest/gtest.h>

#include <fp/lex/tokenize.h>
#include <fp/parse/detail/parser.h>
#include <fp/util/match.h>

namespace fp::parse {

TEST(parse, test) {
    std::string symbols =
R"fp(
a, b for a + b
)fp";

    try {
        auto tokens = lex::tokenize(symbols);
        detail::parser parser;
        ast::node ast = parser.parse(tokens);

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

    } catch (const fp::error& e) {
        const auto& o = e.origin();
        std::cout << "line: " << o.line_number << std::endl << std::endl;

        auto from_col = o.symbols.begin() - o.line;
        auto to_col = from_col + (o.symbols.end() - o.symbols.begin());

        input_view prefix_line(o.line, o.line + from_col);
        input_view error_line(o.line + from_col, o.line + to_col);
        std::cout << prefix_line;
        if (error_line.size() != 0) {
            std::cout << "\033[31m" << error_line << "\033[0m";
        }
        auto it = o.line + to_col;
        while (it != symbols.end() && *it != '\n' && *it != '\r') { ++it; }
        input_view suffix_line(o.line + to_col, it);
        std::cout << suffix_line << std::endl;

        for (size_t i = 0; i < from_col; ++i) { std::cout << " "; }
        std::cout << "\033[31m" << "^";
        if (from_col != to_col) {
            for (size_t i = from_col; i < to_col - 1; ++i) { std::cout << "~"; }
        }
        std::cout << "\033[0m" << std::endl;

        for (size_t i = 0; i < from_col; ++i) { std::cout << " "; }
        std::cout << "\033[1m" << e.what() << "\033[0m" << std::endl;
        std::cout << std::endl;
    }
}

} // fp::lex
