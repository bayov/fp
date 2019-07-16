//#include <fp/util/console/width.h>
//#include <fp/common/detail/diagnostic_printer.h>

#include "problem.h"

namespace fp::diagnostic {

void problem::add_supplement(fp::source_location source, std::string text) {
    supplements_.push_back(supplement { std::move(source), std::move(text) });
}

void problem::add_note(std::string text) {
    notes_.push_back(note { std::move(text) });
}

void problem::add_note(std::string text, fp::source_location source) {
    notes_.push_back(note { std::move(text), std::move(source) });
}

void problem::add_fix_suggestion(
    fp::source_location source,
    source_code replacement
) {
    fix_suggestions_.push_back(
        fix_suggestion { std::move(source), std::move(replacement) }
    );
}

problem::problem(
    diagnostic::severity severity,
    fp::source_location source_location,
    std::string text
) :
    severity_(severity),
    source_location_(std::move(source_location)),
    text_(std::move(text))
{}

problem warning(source_location source, std::string text) {
    return {severity::WARNING, std::move(source), std::move(text)};
}

problem error(source_location source, std::string text) {
    return {severity::ERROR, std::move(source), std::move(text)};
}

//std::ostream& operator<<(std::ostream& os, const diagnostic& d) {
//    detail::diagnostic_printer(d).print(os);
//    return os;
//}

} // namespace fp::diagnostic

//#include <iostream>
//int main() {
//    fp::input_view in =
//R"fp(
//let first = true;
//let second = [1, 2, 3];
//
//
//
//
//
//let x = 42 if first or second else 43;
//# empty line
//)fp";
//
//    auto line1 = &in.front() + 1;
//    auto line2 = line1 + 18;
//    auto line3 = line2 + 29;
//
//    fp::source_location source(
//        fp::input_view(line3 + 20, line3 + 22),
//        line3, 8, in
//    );
//    auto d = fp::problem::error(
//        source,
//        "invalid arguments to `or`: (bool, list[bool])"
//    );
//    fp::source_location lhs(
//        fp::input_view(line3 + 14, line3 + 19),
//        line3, 8, in
//    );
//    d.add_supplement(lhs, "bool");
//    fp::source_location rhs(
//        fp::input_view(line3 + 23, line3 + 29),
//        line3, 8, in
//    );
//    d.add_supplement(rhs, "list[int]");
//
//
//    d.add_note("blah blah blah...");
//    fp::source_location second(
//        fp::input_view(line2 + 4, line2 + 10),
//        line2, 2, in
//    );
//    d.add_note("`second` defined here", second);
//    d.add_supplement(second);
//
//    d.add_fix_suggestion(rhs, "second.empty()");
//
//    std::cout << d << std::endl;
//}
