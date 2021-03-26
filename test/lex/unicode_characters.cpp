#include <gtest/gtest.h>

#include <fp/diagnostic/print/to_terminal.h>
#include <fp/lex/tokenize.h>

namespace fp::lex {

TEST(lex, unicode_characters_not_supported) {
    for (char unicode_char = -128; unicode_char != 0; ++unicode_char) {
        diagnostic::report report;
        fp::source_file file("", std::string_view(&unicode_char, 1));

        tokenized_list tokens = tokenize(file, report);
        if (tokens.size() != 1 || tokens[0].token != token::ERROR) {
            diagnostic::print::to_terminal(std::cout, report);
            ASSERT_EQ(1u, tokens.size()) << "\n"
                << "Expected error token for unicode character: "
                << "\\x" << std::hex << (unsigned char) unicode_char << "\n"
                << "But received " << tokens.size() << " tokens:\n"
                << tokens;
        }

        if (report.errors().empty() || !report.warnings().empty()) {
            diagnostic::print::to_terminal(std::cout, report);
            FAIL()
                << "failed to locate unicode character: \\x"
                << std::hex << (unsigned char) unicode_char;
        }
    }
}

} // namespace fp::lex
