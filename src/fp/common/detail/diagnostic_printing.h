#pragma once

#include <iostream>
#include <iomanip>
#include <map>

#include <fp/util/console/color/color.h>
#include <fp/util/console/colored_text.h>
#include <fp/util/with.h>
#include <fp/common/detail/diagnostic_printer.h>
#include <fp/common/diagnostic.h>

namespace fp::detail {

inline void add_underlines(
    util::console::colored_text& ct,
    const input_view& line,
    const std::list<input_view>& underlines,
    util::console::color::value color
) {
    std::string text = std::string(line.size(), ' ');
    for (auto&& u : underlines) {
        ct.color(color, u.begin() - line.begin(), u.end() - line.begin());
        for (auto it = u.begin(); it != u.end(); ++it) {
            text[it - line.begin()] = '~';
        }
    }
    ct << text;
}

inline void add_arrow(
    util::console::colored_text& ct,
    const input_view& line,
    const input_view& arrow,
    util::console::color::value color
) {
    size_t p = arrow.begin() - line.begin();
    ct.replace_text('^', p, p + 1);
    ct.color(color, p, p + arrow.size());
}

inline void print_diagnostic(std::ostream& os, const diagnostic& d) {
    util::console::color::disable_in_scope disable_colors(
        os.rdbuf() != std::cout.rdbuf() && os.rdbuf() != std::cerr.rdbuf()
    );
    using namespace util::console::color;

    WITH(bold.in_scope(os)) {
        os << blue("<source-file>") << ":";
        size_t column_number = d.source().symbols.begin() - d.source().line;
        os << d.source().line_number << ":" << column_number << ": ";
        if (d.severity() == severity::ERROR) {
            os << red("error");
        } else {
            os << yellow("warning");
        }
        os << ": " << d.text();
    }
    os << std::endl;

    size_t line_number_digits = 3;
    std::map<size_t, input_view> lines;
    std::map<size_t, std::list<input_view>> underlines;
    auto insert_line = [&](const source_location& source) {
        lines.emplace(source.line_number, source_line(source));
        underlines[source.line_number].push_back(source.symbols);
        size_t digits = n_decimal_digits(source.line_number);
        if (digits > line_number_digits) { line_number_digits = digits; }
    };
    insert_line(d.source());
    for (auto&& s : d.supplements()) { insert_line(s.source); }

    size_t prev_line_number = 0;
    for (auto&& item : lines) {
        size_t line_number = item.first;
        input_view line = item.second;
        WITH(gray.in_scope(os)) {
            if (line_number - prev_line_number > 1) {
                os << std::setw(int(line_number_digits)) << "..." << std::endl;
                os << std::setw(int(line_number_digits)) << ' ' << " |" << std::endl;
            }
            os << std::setw(int(line_number_digits)) << line_number << " | ";
        }
        util::console::colored_text colored_line(line);
        util::console::colored_text ct;
        add_underlines(ct, line, underlines[line_number], magenta);
        if (d.source().line_number == line_number) {
            add_arrow(ct, line, d.source().symbols, red);
        }
        os << colored_line << std::endl;
        WITH(gray.in_scope(os)) {
            os << std::setw(int(line_number_digits)) << ' ' << " | ";
        }
        os << ct << std::endl;

        prev_line_number = line_number;
    }
}

} // namespace fp::detail
