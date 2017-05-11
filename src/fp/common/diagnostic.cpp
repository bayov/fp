#include <fp/util/console/width.h>
#include <fp/common/detail/diagnostic_printing.h>
#include <fp/common/detail/diagnostic_printer.h>

#include "diagnostic.h"

namespace fp {

diagnostic diagnostic::error(source_location source, std::string text) {
    return diagnostic(severity::ERROR, std::move(source), std::move(text));
}

diagnostic diagnostic::warning(source_location source, std::string text) {
    return diagnostic(severity::WARNING, std::move(source), std::move(text));
}

fp::severity diagnostic::severity() const { return m_severity; }

const source_location& diagnostic::source() const { return m_source; }

const std::string& diagnostic::text() const { return m_text; }

auto diagnostic::supplements() const -> const std::list<supplement>& {
    return m_source_supplements;
}

auto diagnostic::notes() const -> const std::list<note>& { return m_notes; }

auto diagnostic::fix_suggestions() const -> const std::list<fix_suggestion>& {
    return m_fix_suggestions;
}

void diagnostic::add_supplement(source_location source, std::string text) {
    m_source_supplements.emplace_back(std::move(source), std::move(text));
}

void diagnostic::add_note(std::string text) {
    m_notes.emplace_back(std::move(text), std::optional<source_location>{});
}

void diagnostic::add_note(std::string text, source_location source) {
    m_notes.emplace_back(std::move(text), std::move(source));
}

void diagnostic::add_fix_suggestion(source_location source, input replacement) {
    m_fix_suggestions.emplace_back(std::move(source), std::move(replacement));
}

diagnostic::diagnostic(
    fp::severity severity,
    source_location source,
    std::string text
) :
    m_severity(severity),
    m_source(std::move(source)),
    m_text(std::move(text))
{}

std::ostream& operator<<(std::ostream& os, const diagnostic& d) {
    detail::print_diagnostic(os, d);
    return os;
}

} // namespace fp

int main() {
    fp::input_view in =
R"fp(
let first = true;
let second = [1, 2, 3];





let x = 42 if first or second else 43;
# empty line
)fp";

    auto line1 = &in.front() + 1;
    auto line2 = line1 + 18;
    auto line3 = line2 + 29;

    fp::source_location source(
        fp::input_view(line3 + 20, line3 + 22),
        line3, 8, in
    );
    auto d = fp::diagnostic::error(
        source,
        "invalid arguments to `or`: (bool, list[bool])"
    );
    fp::source_location lhs(
        fp::input_view(line3 + 14, line3 + 19),
        line3, 8, in
    );
    d.add_supplement(lhs, "bool");
    fp::source_location rhs(
        fp::input_view(line3 + 23, line3 + 29),
        line3, 8, in
    );
    d.add_supplement(rhs, "list[int]");


    d.add_note("blah blah blah...");
    fp::source_location second(
        fp::input_view(line2 + 4, line2 + 10),
        line2, 2, in
    );
    d.add_note("`second` defined here", second);
    d.add_supplement(second);

    d.add_fix_suggestion(rhs, "second.empty()");

    fp::detail::diagnostic_printer printer(d);
    printer.print(std::cout);
    std::cout << std::endl;
    std::cout << "=============================" << std::endl;

    std::cout << d << std::endl;
    std::cout << "=============================" << std::endl;
}
