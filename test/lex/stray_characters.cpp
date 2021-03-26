#include <gtest/gtest.h>

#include <fp/diagnostic/print/to_terminal.h>
#include <fp/lex/tokenize.h>

namespace fp::lex {

void assert_stray_character(std::string_view source_str) {
    diagnostic::report report;
    fp::source_file file("", source_str);

    int16_t value = source_str[0];

    tokenized_list tokens = tokenize(file, report);
    if (tokens.size() != 1 || tokens[0].token != token::ERROR) {
        diagnostic::print::to_terminal(std::cout, report);
        ASSERT_EQ(1u, tokens.size()) << "\n"
            << "Expected error token for stray character: "
            << "\\" << std::oct << value << "\n"
            << "But received " << tokens.size() << " tokens:\n"
            << tokens;
    }

    if (report.errors().size() != 1 || !report.warnings().empty()) {
        diagnostic::print::to_terminal(std::cout, report);
        FAIL() << "failed to locate stray character: \\" << std::oct << value;
    }

    ASSERT_EQ(
        report.errors().front().error_code(),
        &error::E0001_stray_character
    );
}

TEST(lex, stray_characters) {
    assert_stray_character(std::string_view("\0", 1)); // NUL (null)

    assert_stray_character("\1");  // SOH (start of header)
    assert_stray_character("\2");  // STX (start of text)
    assert_stray_character("\3");  // ETX (end of text)
    assert_stray_character("\4");  // EOT (end of transmission)
    assert_stray_character("\5");  // ENQ (enquiry)
    assert_stray_character("\6");  // ACK (acknowledge)
    assert_stray_character("\7");  // BEL (bell)
    assert_stray_character("\10"); // BS (backspace)

    // \11 to \15 are whitespace characters

    assert_stray_character("\16"); // SO (shift out)
    assert_stray_character("\17"); // SI (shift in)
    assert_stray_character("\20"); // DLE (data link escape)
    assert_stray_character("\21"); // DC1 (device control 1)
    assert_stray_character("\22"); // DC2 (device control 2)
    assert_stray_character("\23"); // DC3 (device control 3)
    assert_stray_character("\24"); // DC4 (device control 4)
    assert_stray_character("\25"); // NAK (negative acknowledge)
    assert_stray_character("\26"); // SYN (synchronous idle)
    assert_stray_character("\27"); // ETB (end of transmission block)
    assert_stray_character("\30"); // CAN (cancel)
    assert_stray_character("\31"); // EM (end of medium)
    assert_stray_character("\32"); // SUB (substitute)
    assert_stray_character("\33"); // ESC (escape)
    assert_stray_character("\34"); // FS (file separator)
    assert_stray_character("\35"); // GS (group separator)
    assert_stray_character("\36"); // RS (record separator)
    assert_stray_character("\37"); // US (unit separator)

    assert_stray_character("$");
    assert_stray_character("\\");
    assert_stray_character("`");

    assert_stray_character("\177"); // DEL (delete)
}

} // namespace fp::lex
