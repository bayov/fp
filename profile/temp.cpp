#include <iostream>

#include <gperftools/profiler.h>

#include <fp/common/input.h>
#include <fp/lex/tokenize.h>

using namespace fp;
using namespace fp::lex;

int main() {

    input in =
        R"fp(
# test, test, 1, 2, 3...
'"'
"hello, {"from the other {"side of the plant"}..."}"
"look, {"a wild brace:" { 3 { 4 } 1 + 1 } "bla" }"
)fp";

    for (size_t i = 0; i < 12; ++i) {
        in += in;
    }

    input_view symbols(in);

    try {
        ProfilerStart("temp.prof");
        for (size_t i = 0; i < 100; ++i) {
            ProfilerEnable();
            auto tokens = tokenize(symbols);
            ProfilerDisable();
            std::cout << tokens.size() << std::endl;
        }
        ProfilerStop();
    } catch (const fp::diagnostic& e) {
        const auto& o = e.source();
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
