#pragma once

#include <iostream>
#include <iomanip>
#include <map>

#include <fp/util/color_value.h>
#include <fp/util/colored_text.h>
#include <fp/util/with.h>
#include <fp/common/diagnostic.h>

namespace fp::detail {

inline size_t n_decimal_digits(size_t n) {
    return n < 10 ? 1 : 1 + n_decimal_digits(n / 10);
}

inline input_view source_line(const source_location& source) {
    auto it = source.line;
    while (it != source.input.end() && *it != '\r' && *it != '\n') { ++it; }
    return { source.line, it };
}

inline void add_underlines(
    util::color::colored_text& ct,
    const input_view& line,
    const std::list<input_view>& underlines,
    util::color::color_value color
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
    util::color::colored_text& ct,
    const input_view& line,
    const input_view& arrow,
    util::color::color_value color
) {
    size_t p = arrow.begin() - line.begin();
    ct.replace_text('^', p, p + 1);
    ct.color(color, p, p + arrow.size());
}

inline void print_diagnostic(std::ostream& os, const diagnostic& d) {
    util::color::disable_in_scope disable_colors(
        os.rdbuf() != std::cout.rdbuf() && os.rdbuf() != std::cerr.rdbuf()
    );
    using namespace util::color;

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
        os << line << std::endl;
        WITH(gray.in_scope(os)) {
            os << std::setw(int(line_number_digits)) << ' ' << " | ";
        }
        colored_text ct;
        add_underlines(ct, line, underlines[line_number], magenta);
        if (d.source().line_number == line_number) {
            add_arrow(ct, line, d.source().symbols, red);
        }
        os << ct << std::endl;

        prev_line_number = line_number;
    }
}

} // namespace fp::detail
