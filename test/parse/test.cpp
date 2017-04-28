#include <gtest/gtest.h>

#include <fp/lex/tokenize.h>
#include <fp/parse/parse.h>

namespace fp::parse {

TEST(parse, test) {
    std::string symbols =
R"fp(
1 + 2 + 3
)fp";

    auto tokens = lex::tokenize(symbols);
    parse(tokens);
}

} // fp::lex
