#pragma once

#include <sstream>
#include <string_view>
#include <map>
#include <list>

#include <fp/util/console/color/color.h>
#include <fp/util/named_tuple.h>

namespace fp::util::console {

/**
 * A simply utility to help coloring lines of text before printing them.
 *
 * @see fp::util::color::color_value
 *
 * @example
 *
 *      colored_text ct("rgb = ");
 *      ct << 100 << ',' << 22 << ',' << 3;
 *      ct.color(red, 6, 9);        // [6,9) is the "100" portion of the text
 *      ct.color(green, 10, 12);    // [10,12) is the "22" portion of the text
 *      ct.color(blue, 13, 14);     // [13,14) is the "3" portion of the text
 *
 *      std::cout << ct << std::endl;
 *      // prints `rgb = 100,22,3` with each component appropriately colored
 */
class colored_text {
public:

    colored_text() = default;

    /// Equivalent to `colored_text ct(); ct << v;`.
    template <class T>
    explicit colored_text(T&& v) { *this << std::forward<T>(v); }

    template <class T>
    std::ostream& operator<<(T&& v) { return m_text << std::forward<T>(v); }

    void color(const color::value& c, size_t from, size_t to) {
        m_color_codes[from].push_back({ c.open });
        m_color_codes[to].push_back({ c.close });
    }

    /**
     * Replace the text in portion `[from, to)` with the given value.
     *
     * If the text is too short (i.e., `to` is out of range), the text will
     * be padded with `pad` characters.
     */
    template <class T>
    void replace_text(T&& v, size_t from, size_t to, char pad = ' ') {
        auto s = m_text.str();
        if (to > s.size()) { s += std::string(to - s.size() + 1, pad); }
        m_text = std::stringstream();
        m_text << std::string_view(&s[0], from);
        m_text << v;
        m_text << std::string_view(&s[to], s.size() - to);
    }

    friend std::ostream& operator<<(std::ostream& os, const colored_text& ct) {
        auto s = ct.m_text.str();
        size_t i = 0;
        for (auto& cc : ct.m_color_codes) {
            size_t col = cc.first;
            auto& codes = cc.second;
            // print up to the color codes' column
            os << std::string_view(&s[i], col - i);
            // print the color codes
            for (auto& code : codes) { os << code; }
            i = col;
        }
        // print the remaining text
        os << std::string_view(&s[i], s.size() - i);
        return os;
    }

private:

    std::stringstream m_text;
    std::map<size_t, std::list<color::code>> m_color_codes;

};

} // namespace fp::util::console
