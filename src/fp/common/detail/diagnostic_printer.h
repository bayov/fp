#pragma once

#include <ostream>

#include <fp/util/console/text_formatter.h>
#include <fp/util/console/fill.h>
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

class diagnostic_printer {
public:

    const diagnostic& d;

    explicit diagnostic_printer(const diagnostic& d) : d(d) {
        initialize();
        m_t << std::endl;
        write_header();
        m_t << std::endl;
        write_source();
    }

    void print(std::ostream& os) { os << m_t; }

private:

    util::console::text_formatter m_t;
    size_t m_gutter_width = 3;
    std::map<size_t, input_view> m_lines;
    std::map<size_t, std::list<input_view>> m_underlines;

    void insert_line(const source_location& src) {
        m_lines.emplace(src.line_number, source_line(src));
        m_underlines[src.line_number].push_back(src.symbols);
        size_t digits = n_decimal_digits(src.line_number);
        if (digits > m_gutter_width) { m_gutter_width = digits; }
    }

    void initialize() {
        insert_line(d.source());
        for (auto&& s : d.supplements()) { insert_line(s.source); }
    }

    void write_header() {
        using namespace util::console::color;
        WITH(m_t.color(bold)) {
            m_t << blue("<source-file>") << ':';
            m_t << d.source().line_number << ':';
            m_t << (d.source().symbols.begin() - d.source().line) << ": ";
            if (d.severity() == severity::ERROR) {
                m_t << red("error");
            } else {
                m_t << yellow("warning");
            }
            m_t << ": ";
            if (m_t.current_line_length() * 2 > m_t.width()) {
                m_t << std::endl << "    ";
            }
            WITH(m_t.prefix(std::string(m_t.current_line_length(), ' '))) {
                m_t << d.text();
            }
        }
    }

    void write_source() {
        using namespace util::console::color;
        using util::console::fill;
        size_t prev_line_number = 0;
        for (auto&& item : m_lines) {
            size_t line_number = item.first;
            const input_view& line = item.second;
            WITH(m_t.color(gray)) {
                if (line_number - prev_line_number > 1) {
                    m_t << fill(m_gutter_width, "...") << std::endl;
                    m_t << fill(m_gutter_width, "") << " |" << std::endl;
                }
                m_t << fill(m_gutter_width, line_number) << " | ";
            }
            m_t << line << std::endl;
            WITH(m_t.color(gray)) {
                m_t << fill(m_gutter_width, "") << " |";
            }
            m_t << std::endl;
        }
    }

};

} // namespace fp::detail
