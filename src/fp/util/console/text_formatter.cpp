#include "text_formatter.h"

namespace fp::util::console {

namespace detail {

std::pair<std::string_view, std::string_view> split_text(
    const std::string_view& s,
    size_t pos
) {
    if (pos == 0) { return { {}, s }; }
    std::pair<std::string_view, std::string_view> result;
    auto it = s.begin() + pos;
    while (!std::isspace(*it)) {
        --it;
        if (it == s.begin()) {
            // no space to split at, so we have to split at the given `pos`
            it = s.begin() + pos;
            break;
        }
    }

    // strip trailing whitespace
    auto left_it = it;
    while (std::isspace(*left_it)) { --left_it; }

    // strip leading whitespace
    auto right_it = it;
    while (std::isspace(*right_it)) { ++right_it; }

    if (left_it == right_it) { --left_it; }

    result.first = std::string_view(&s.front(), left_it - s.begin() + 1);
    result.second = std::string_view(&*right_it, s.end() - right_it);
    return result;
}

} // namespace detail

text_formatter::color_in_scope::color_in_scope(
    color::value c,
    std::list<color::value>& cs
) :
    cs(cs), it(cs.insert(cs.end(), std::move(c)))
{}

text_formatter::color_in_scope::~color_in_scope() { cs.erase(it); }

text_formatter::prefix_in_scope::prefix_in_scope(
    prefix_t p,
    std::list<prefix_t>& ps
) :
    ps(ps), it(ps.insert(ps.end(), std::move(p)))
{}

text_formatter::prefix_in_scope::~prefix_in_scope() { ps.erase(it); }

text_formatter::text_formatter() : text_formatter(console::width()) {}

text_formatter::text_formatter(size_t width) : m_width(width) { newline(); }

void text_formatter::newline() {
    m_lines.emplace_back();
    m_lines.back().text.reserve(m_width);
    for (auto&& p : m_prefixes_in_scope) { write(p.text, p.colors); }
}

text_formatter& text_formatter::operator<<(std::ostream& (&m)(std::ostream&)) {
    if (m == std::endl<char, std::char_traits<char>>) {
        newline();
    } else {
        write(m, {});
    }
    return *this;
}

auto text_formatter::color(const color::value& c) -> color_in_scope {
    return color_in_scope(c, m_colors_in_scope);
}

size_t text_formatter::width() const { return m_width; }

size_t text_formatter::current_line_length() const {
    return m_lines.back().text.size();
}

std::ostream& operator<<(std::ostream& os, const text_formatter& t) {
    auto it = t.m_lines.begin();
    os << *it++;
    for (; it != t.m_lines.end(); ++it) { os << std::endl << *it; }
    return os;
}

void text_formatter::write(
    const std::string& s,
    const std::list<color::value>& colors
) {
    write(std::string_view(&s.front(), s.size()), colors);
}

void text_formatter::write(
    const char* s,
    const std::list<color::value>& colors
) {
    write(std::string_view(s), colors);
}

void text_formatter::write(
    const std::string_view& s,
    const std::list<color::value>& colors
) {
    if (s.size() == 0) { return; }
    auto& line = m_lines.back();
    if (line.text.size() + s.size() > m_width) {
        auto split = detail::split_text(s, m_width - line.text.size());
        write(split.first, colors);
        newline();
        write(split.second, colors);
        return;
    }
    size_t from = line.text.size();
    line.text += s;
    size_t to = line.text.size();
    for (auto&& c : m_colors_in_scope) {
        line.color_codes[from].push_back({ c.open });
        line.color_codes[to].push_back({ c.close });
    }
    for (auto&& c : colors) {
        line.color_codes[from].push_back({ c.open });
        line.color_codes[to].push_back({ c.close });
    }
}

std::ostream& operator<<(std::ostream& os, const text_formatter::line_t& line) {
    size_t i = 0;
    for (auto& cc : line.color_codes) {
        size_t col = cc.first;
        auto& codes = cc.second;
        // print up to the color codes' column
        os << std::string_view(&line.text[i], col - i);
        // print the color codes
        for (auto& code : codes) { os << code; }
        i = col;
    }
    // print the remaining text
    os << std::string_view(&line.text[i], line.text.size() - i);
    return os;
}
} // namespace fp::util::console
