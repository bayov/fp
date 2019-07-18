#include <fp/lex/tokenize.h>

#include <test-util/catergorized_test.h>

namespace fp::lex {

#define TEST(what) CATEGORIZED_TEST(lex, tokenize, what)

TEST(for_each) {
    source_view source_code = R"source_code(
        '\z
    )source_code";
    diagnostic::report report;
    tokenized_list tokens = tokenize(source_code, report);

    std::cout << "-----------------------------------------------" << std::endl;
    for (const tokenized_token& token : tokens) {
        std::cout << token << std::endl;
    }
    std::cout << "-----------------------------------------------" << std::endl;
    for (const diagnostic::problem& error : report.errors()) {
        auto s = error.source_location();
        std::cout << "/mnt/b/wsl/project/fp/source_code.fp:" << s.line_number << ':';
        std::cout << (s.chars.begin() - s.line) << ": ";
        auto escape = [](size_t number) { std::cout << "\033[" << number << 'm'; };
        escape(31);
        escape(1);
        std::cout << "error: ";
        escape(22);
        escape(39);
        std::cout << error.text() << std::endl;
        std::cout << "    " << s.line_number << " | ";
        source_iterator line_end = s.line;
        while (line_end != s.source_code.end() && *line_end != '\n') {
            ++line_end;
        }
        std::cout << make_source_view(s.line, line_end) << std::endl;
        std::cout << "      | ";
        escape(31);
        std::cout << std::string((s.chars.begin() - s.line), ' ') << '^';
        std::cout << std::string((s.chars.size() - 1), '~') << std::endl;
        escape(39);
    }
}

} // namespace fp::lex
