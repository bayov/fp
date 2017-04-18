#include <gtest/gtest.h>

#include <fp/lex/attribute.h>
#include <fp/lex/error.h>
#include <fp/lex/symbol.h>
#include <fp/lex/token.h>
#include <fp/lex/token_list.h>
#include <fp/lex/token_source.h>
#include <fp/lex/tokenize.h>
#include <fp/util/named_tuple.h>

namespace fp::lex {

TEST(fiddle, test) {
    std::cout << std::endl;
    std::cout << std::endl;

    std::string symbols =
R"fp(
# test, test, 1, 2, 3...
"one plus one plus million is {1 + 1 + 1`000`000}"
"hello, {"from the other {"side of the plant"}..."}"
"look, {"a wild brace:" { 3 { 4 } 1 + 1 } "bla" }"
)fp";

    try {
        auto tokens = tokenize(symbols);

        std::cout << "Source code:" << std::endl;
        std::cout << "============" << std::endl;
        std::cout << symbols << std::endl;
        std::cout << "------------" << std::endl;
        std::cout << std::endl;

        std::cout << "After tokenization:" << std::endl;
        std::cout << "===================" << std::endl;
        size_t line = tokens.front().source.line_number;
        std::string source_line;
        std::string tokens_line;
        for (const auto& t : tokens) {
            if (t.source.line_number > line) {
                std::cout << source_line << std::endl;
                std::cout << tokens_line << std::endl;
                line = t.source.line_number;
                source_line.clear();
                tokens_line.clear();
            }
            std::string source_str(t.source.symbols.view());
            std::string token_str(util::enumerator(t.value).name());
            switch (t.value) {
                case token::COMMENT:
                    token_str += "(" + std::string(t.attribute.as<token::COMMENT>()) + ")";
                    break;
                case token::IDENTIFIER:
                    token_str += "(" + std::string(t.attribute.as<token::IDENTIFIER>()) + ")";
                    break;
                case token::INTEGER:
                    token_str += "(" + std::to_string(t.attribute.as<token::INTEGER>()) + ")";
                    break;
                case token::FLOAT:
                    token_str += "(" + std::to_string(t.attribute.as<token::FLOAT>()) + ")";
                    break;
                case token::STRING:
                    token_str += "(" + std::string(t.attribute.as<token::STRING>()) + ")";
                    break;
                default:
                    break;
            }

            while (source_str.size() > token_str.size()) { token_str += ' '; }
            while (token_str.size() > source_str.size()) { source_str += ' '; }
            source_str = "\033[100m" + source_str + "\033[0m";
            token_str = "\033[34m" + token_str + "\033[0m";

            source_line += source_str + "  ";
            tokens_line += token_str + "  ";
        }
        std::cout << source_line << std::endl;
        std::cout << tokens_line << std::endl;
        std::cout << "-------------------" << std::endl;
        std::cout << std::endl;

    } catch (const fp::lex::error& e) {
        std::cout << "line: " << e.line_number << std::endl << std::endl;

        auto from_col = e.symbols.begin() - e.line;
        auto to_col = from_col + (e.symbols.end() - e.symbols.begin());

        input_view_t prefix_line(e.line, e.line + from_col);
        input_view_t error_line(e.line + from_col, e.line + to_col);
        std::cout << prefix_line;
        if (error_line.size() != 0) {
            std::cout << "\033[41m" << error_line << "\033[0m";
        }
        auto it = e.line + to_col;
        while (it != symbols.end() && *it != '\n' && *it != '\r') { ++it; }
        input_view_t suffix_line(e.line + to_col, it);
        std::cout << suffix_line << std::endl;

        for (size_t i = 0; i < from_col - 1; ++i) { std::cout << " "; }
        std::cout << " \033[31m" << "^";
        for (size_t i = from_col; i < to_col - 1; ++i) { std::cout << "~"; }
        std::cout << "\033[0m" << std::endl;

        for (size_t i = 0; i < from_col - 1; ++i) { std::cout << " "; }
        std::cout << " \033[1m" << e.what() << "\033[0m" << std::endl;
        std::cout << std::endl;
    }
}

} // fp::lex
