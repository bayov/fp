#include <fp/util/with.h>
#include <fp/util/console/width.h>
#include <fp/util/console/fill.h>

#include "diagnostic_printer.h"

namespace fp::detail {

using namespace util::console;
using namespace color;

static constexpr size_t MIN_WIDTH = 40;

static constexpr auto SOURCE_FILE_COLOR = blue;
static constexpr auto GUTTER_COLOR      = gray;
static constexpr auto CODE_COLOR        = gray;
static constexpr auto SUPPLEMENT_COLOR  = normal;
static constexpr auto UNDERLINE_COLOR   = red;

inline size_t n_decimal_digits(size_t n) {
    return n < 10 ? 1 : 1 + n_decimal_digits(n / 10);
}

inline input_view source_line(const source_location& source) {
    auto it = source.line;
    while (it != source.input.end() && *it != '\r' && *it != '\n') { ++it; }
    return { source.line, it };
}

diagnostic_printer::diagnostic_printer(const diagnostic& d) :
    d(d),
    m_t(width())
{
    initialize();
    m_t << std::endl;
    write_header();
    m_t << std::endl;
    write_source();
}

void diagnostic_printer::print(std::ostream& os) { os << m_t; }

size_t diagnostic_printer::width() {
    size_t console_width = util::console::width();
    return console_width < MIN_WIDTH ? MIN_WIDTH : console_width;
}

void diagnostic_printer::insert_line(const source_location& src) {
    m_lines.emplace(src.line_number, source_line(src));
    m_underlines[src.line_number].push_back(src.symbols);
    size_t digits = n_decimal_digits(src.line_number);
    if (digits > m_gutter_width) { m_gutter_width = digits; }
}

void diagnostic_printer::initialize() {
    insert_line(d.source());
    for (auto&& s : d.supplements()) { insert_line(s.source); }
}

void diagnostic_printer::write_header() {
    WITH(m_t.color(bold)) {
        m_t << SOURCE_FILE_COLOR("<source-file>") << ':';
        m_t << d.source().line_number << ':';
        m_t << (d.source().symbols.begin() - d.source().line) << ": ";
        if (d.severity() == severity::ERROR) {
            m_t << red("error");
        } else {
            m_t << yellow("warning");
        }
        m_t << ": ";
        if (m_t.current_line_length() + d.text().size() > m_t.width()) {
            m_t << std::endl << "    ";
        }
        WITH(m_t.prefix(std::string(m_t.current_line_length(), ' '))) {
            m_t << d.text();
        }
    }
}

void diagnostic_printer::write_source() {
    size_t prev_line_number = 0;
    for (auto&& item : m_lines) {
        size_t line_number = item.first;
        WITH(m_t.color(GUTTER_COLOR)) {
            if (line_number - prev_line_number > 1) {
                m_t << fill(m_gutter_width, "...") << std::endl;
                m_t << fill(m_gutter_width, "") << " |" << std::endl;
            }
        }
        write_source_line(line_number);
    }
}

void diagnostic_printer::write_source_line(size_t n) {
    const input_view& line = m_lines.at(n);

    WITH(m_t.color(GUTTER_COLOR)) { m_t << fill(m_gutter_width, n) << " | "; }
    WITH(m_t.color(CODE_COLOR)) {
        write_colorized_line(line, n, SUPPLEMENT_COLOR);
    }
    WITH(m_t.color(GUTTER_COLOR)) { m_t << fill(m_gutter_width, "") << " | "; }
    WITH(m_t.color(CODE_COLOR)) {
        write_colorized_line(underlines(n), n, UNDERLINE_COLOR);
    }
}

void diagnostic_printer::write_colorized_line(
    const input_view& line,
    size_t n,
    const util::console::color::value& c
) {
    size_t margin_left = m_t.current_line_length();
    auto lit = m_lines.at(n).begin();
    m_t << line;
    for (auto&& u : m_underlines.at(n)) {
        m_t.colorize(
            c,
            u.begin() - lit + margin_left,
            u.end() - lit + margin_left
        );
    }
    if (d.source().line_number == n) {
        m_t.colorize(
            bold,
            d.source().symbols.begin() - lit + margin_left,
            d.source().symbols.end() - lit + margin_left
        );
    }
    m_t << std::endl;
}

std::string diagnostic_printer::underlines(size_t n) const {
    std::string r;
    auto lit = m_lines.at(n).begin();
    for (auto&& u : m_underlines.at(n)) {
        if (u.end() - lit > r.size()) { r.resize(u.end() - lit, ' '); }
        for (auto it = u.begin(); it != u.end(); ++it) {
            r[it - lit] = '~';
        }
    }
    if (d.source().line_number == n) {
        r[d.source().symbols.begin() - lit] = '^';
    }
    return r;
}

} // namespace fp::detail
