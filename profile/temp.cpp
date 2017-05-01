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

    for (size_t i = 0; i < 10; ++i) {
        in += in;
    }

    input_view symbols(in);

    ProfilerStart("temp.prof");
    for (size_t i = 0; i < 500; ++i) {
        diagnostic_report diagnostics;
        ProfilerEnable();
        auto tokens = tokenize(symbols, diagnostics);
        ProfilerDisable();
        std::cout << tokens.size() << std::endl;
    }
    ProfilerStop();
}
