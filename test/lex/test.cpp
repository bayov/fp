#include <gtest/gtest.h>

#include <fp/lex/attribute.h>
#include <fp/lex/error.h>
#include <fp/lex/symbol.h>
#include <fp/lex/token.h>
#include <fp/lex/token_list.h>
#include <fp/lex/token_source.h>
#include <fp/lex/tokenize.h>
#include <fp/util/fundamental.h>
#include <fp/util/named_tuple.h>

namespace fp::lex {

TEST(fiddle, test) {
    std::cout << std::endl;
    std::cout << std::endl;
    std::string symbols =
        "0xf`f  \" \t\n  \r\n !=\" # comment! = \t\"\r\n!=  !=";
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
                std::cout << std::endl;
                line = t.source.line_number;
                source_line.clear();
                tokens_line.clear();
            }
            std::string source_str(t.source.symbols);
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

            source_line += source_str + "  ";
            tokens_line += token_str + "  ";
        }
        std::cout << source_line << std::endl;
        std::cout << tokens_line << std::endl;
        std::cout << "-------------------" << std::endl;
        std::cout << std::endl;

    } catch (const fp::lex::error& e) {
        std::cout << "line: " << e.line_number << std::endl << std::endl;

        auto it = e.line;
        while (it != symbols.end() && *it != '\n' && *it != '\r') { ++it; }
        input_view_t line(e.line, it);
        std::cout << line << std::endl;

        it = e.symbols.begin();
        auto from_col = 1 + (it - e.line);
        auto to_col = from_col + (e.symbols.end() - it);

        for (size_t i = 0; i < from_col - 1; ++i) { std::cout << " "; }
        std::cout << "^";
        for (size_t i = from_col; i < to_col - 1; ++i) { std::cout << "~"; }
        std::cout << std::endl;

        for (size_t i = 0; i < from_col - 1; ++i) { std::cout << " "; }
        std::cout << e.what() << std::endl;
        std::cout << std::endl;
    }
}

} // fp::lex
