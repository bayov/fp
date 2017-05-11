#pragma once

#include <ostream>

#include <fp/util/console/text_formatter.h>
#include <fp/common/diagnostic.h>

namespace fp::detail {

class diagnostic_printer {
public:

    const diagnostic& d;

    explicit diagnostic_printer(const diagnostic& d);

    void print(std::ostream& os);

private:

    util::console::text_formatter m_t;
    size_t m_gutter_width = 3;
    std::map<size_t, input_view> m_lines;
    std::map<size_t, std::list<input_view>> m_underlines;

    static size_t width();

    void insert_line(const source_location& src);
    void initialize();
    void write_header();
    void write_source();
    void write_source_line(size_t n);

    void write_colorized_line(
        const input_view& line,
        size_t n,
        const util::console::color::value& c
    );

    std::string underlines(size_t n) const;

};

} // namespace fp::detail
