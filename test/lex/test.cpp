#include <gtest/gtest.h>

#include <fp/util/named_tuple.h>

#include <fp/common/types.h>
#include <fp/common/source_location.h>
#include <fp/common/diagnostic.h>

#include <fp/lex/attribute.h>
#include <fp/lex/token.h>
#include <fp/lex/token_list.h>
#include <fp/lex/tokenize.h>

namespace fp::lex {

TEST(fiddle, test) {
    std::cout << std::endl;
    std::cout << std::endl;

    input_view symbols =
R"fp(
123`
1``3
'"'
"hello, {"from the other {"side of the plant"}..."}"
"look, {"brace:" { 3 { 4 } 1 } 42 }"
)fp";

    diagnostic_report diagnostics;
    auto tokens = tokenize(symbols, diagnostics);

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
        std::string source_str(t.source.symbols);
        std::string token_str(util::info(t.value).name());
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
            case token::CHAR:
                token_str += "(" + std::string(1, t.attribute.as<token::CHAR>()) + ")";
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

    for (auto& d : diagnostics.errors()) {
        const auto& o = d.source();
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
        std::cout << "\033[1m" << d.text() << "\033[0m" << std::endl;
        std::cout << std::endl;
    }
}

} // fp::lex
