#include <gtest/gtest.h>

#include <fp/diagnostic/print/to_terminal.h>
#include <fp/lex/tokenize.h>

namespace fp::lex {

template <token EXPECTED_TOKEN>
void assert_single_token(std::string_view source_str) {
    std::string_view name = token_name(EXPECTED_TOKEN);
    diagnostic::report report;
    fp::source_file file("single-token-test.fp", source_str);

    tokenized_list tokens = tokenize(file, report);
    if (!report.errors().empty() || !report.warnings().empty()) {
        diagnostic::print::to_terminal(std::cout, report);
        FAIL() << name;
    }

    ASSERT_EQ(1u, tokens.size()) << "\n"
        << "Expected single token: token::" << name << "\n"
        << "But received " << tokens.size() << " tokens:\n"
        << tokens;
    ASSERT_EQ(EXPECTED_TOKEN, tokens[0].token);
    ASSERT_FALSE(tokens[0].dummy) << name;

    using attribute_t = token_attribute_t<EXPECTED_TOKEN>;
    using expected_attribute_t = std::conditional_t<
        std::is_void_v<attribute_t>,
        std::monostate,
        attribute_t
    >;
    ASSERT_TRUE(std::holds_alternative<expected_attribute_t>(
        tokens[0].attribute
    )) << name;

    const auto& location = tokens[0].source_location;
    ASSERT_EQ(file.content        , location.chars      ) << name;
    ASSERT_EQ(file                , location.file       ) << name;
    ASSERT_EQ(file.content.begin(), location.line       ) << name;
    ASSERT_EQ(1u                  , location.line_number) << name;
}

TEST(lex, single_tokens) {
    assert_single_token<token::COMMA>(",");
    assert_single_token<token::ANNOTATION>(":");
    assert_single_token<token::SCOPE>("::");
    assert_single_token<token::SEMICOLON>(";");
    assert_single_token<token::OPTIONAL>("?");
    assert_single_token<token::DECORATOR>("@");
    assert_single_token<token::BIT_NOT>("~");
    assert_single_token<token::MEMBER_ACCESS>(".");
    // TODO: tokenize ranges
//    assert_single_token<token::RANGE>("..");
//    assert_single_token<token::CLOSED_RANGE>("...");

    // brackets
    assert_single_token<token::L_PAREN>("(");
    assert_single_token<token::R_PAREN>(")");
    assert_single_token<token::L_BRACKET>("[");
    assert_single_token<token::R_BRACKET>("]");
    assert_single_token<token::L_BRACE>("{");
    assert_single_token<token::R_BRACE>("}");

    // keywords
    assert_single_token<token::AND>("and");
    assert_single_token<token::AS>("as");
    assert_single_token<token::BREAK>("break");
    assert_single_token<token::CASE>("case");
    assert_single_token<token::CATCH>("catch");
    assert_single_token<token::CLASS>("class");
    assert_single_token<token::CONCEPT>("concept");
    assert_single_token<token::CONTINUE>("continue");
    assert_single_token<token::DEFAULT>("default");
    assert_single_token<token::DO>("do");
    assert_single_token<token::ELSE>("else");
    assert_single_token<token::ENUM>("enum");
    assert_single_token<token::EXPORT>("export");
    assert_single_token<token::FOR>("for");
    assert_single_token<token::IF>("if");
    assert_single_token<token::IMPLICIT>("implicit");
    assert_single_token<token::IMPORT>("import");
    assert_single_token<token::IN>("in");
    assert_single_token<token::MUT>("mut");
    assert_single_token<token::NOT>("not");
    assert_single_token<token::OF>("of");
    assert_single_token<token::OR>("or");
    assert_single_token<token::RETURN>("return");
    assert_single_token<token::SWITCH>("switch");
    assert_single_token<token::THROW>("throw");
    assert_single_token<token::TRY>("try");
    assert_single_token<token::WHILE>("while");

    // arrows
    assert_single_token<token::TYPE_ARROW>("->");
    assert_single_token<token::LAMBDA_ARROW>("=>");

    // arithmetic
    assert_single_token<token::ADD>("+");
    assert_single_token<token::SUB>("-");
    assert_single_token<token::MUL>("*");
    assert_single_token<token::DIV>("/");
    assert_single_token<token::MOD>("%");
    assert_single_token<token::POW>("^");
    assert_single_token<token::BIT_AND>("&");
    assert_single_token<token::BIT_OR>("|");
    // TODO: Goddamn xor...
//    assert_single_token<token::XOR>("^");
    assert_single_token<token::SHL>("<<");
    assert_single_token<token::SHR>(">>");

    // assignments
    assert_single_token<token::ASSIGN>("=");
    assert_single_token<token::ADD_ASSIGN>("+=");
    assert_single_token<token::SUB_ASSIGN>("-=");
    assert_single_token<token::MUL_ASSIGN>("*=");
    assert_single_token<token::DIV_ASSIGN>("/=");
    assert_single_token<token::MOD_ASSIGN>("%=");
    assert_single_token<token::POW_ASSIGN>("^=");
    assert_single_token<token::BIT_AND_ASSIGN>("&=");
    assert_single_token<token::BIT_OR_ASSIGN>("|=");
    // TODO: Goddamn xor...
//    assert_single_token<token::XOR_ASSIGN>("^=");
    assert_single_token<token::SHL_ASSIGN>("<<=");
    assert_single_token<token::SHR_ASSIGN>(">>=");

    // comparisons
    assert_single_token<token::EQ>("==");
    assert_single_token<token::NE>("!=");
    assert_single_token<token::LT>("<");
    assert_single_token<token::GT>(">");
    assert_single_token<token::LTE>("<=");
    assert_single_token<token::GTE>(">=");

    // increment & decrement
    assert_single_token<token::INC>("++");
    assert_single_token<token::DEC>("--");

    // containing attributes
    assert_single_token<token::COMMENT>("# hello");
    assert_single_token<token::IDENTIFIER>("foo_bar");
    assert_single_token<token::NUMBER>("42");
    assert_single_token<token::CHAR>("'c'");
    // assert_single_token<token::STRING>(can't be produced as a single token);
}

} // namespace fp::lex
