#pragma once

#include <vector>
#include <map>
#include <list>

#include <fp/util/as_string.h>
#include <fp/util/context_list.h>
#include <fp/util/console/color/color.h>

namespace fp::util::console {

namespace detail {

struct text_formatter_prefix {

    std::string text;
    std::list<color::value> colors;

    template <class T>
    static text_formatter_prefix create(
        const T& v,
        std::list<color::value> colors
    ) {
        return { as_string(v), std::move(colors) };
    }

    template <class T>
    static text_formatter_prefix create(
        const color::value::wrapper<T>& w,
        std::list<color::value> colors
    ) {
        colors.push_back(w.c);
        return create(w.v, std::move(colors));
    }

};

} // namespace detail

/**
 * A simple utility to help printing lines of text that are both colored and
 * broken down to remain under a given width.
 *
 * @example
 *
 *      text_formatter t(10);   // max text width is 10
 *
 *      t << "hello ";          // writes "hello "
 *
 *      t << red("world");      // writes "world" in green
 *                              // "world is written in a new-line, since the
 *                              // string "hello world" exceeds 10 characters
 *
 *      t << std::endl;         // write a new-line
 *
 *      WITH(t.prefix(gray(">> "))) {
 *          // in this scope, newlines will be prefixed with a gray ">> "
 *
 *          t << std::endl;     // writes a new-line and ">> "
 *
 *          t << red("12345 12345");
 *          // the above call will write "12345" and the next "12345" in a new-
 *          // line (since it exceeds max-width). Since a new-line is
 *          // introduced, and the prefix is set to be a gray ">> ", what will
 *          // be written on the new-line is ">> 12345", prefix in gray, text in
 *          // red.
 *      }
 *
 *      WITH(t.color(red)) {
 *          // all writes in this scope will be wrapped in a red color.
 *          // ...
 *      }
 *
 *      std::cout << t;         // print the written text stdout
 */
class text_formatter {
public:

    /// Construct a text-formatter with width `console::width()`.
    text_formatter();

    /// Construct a text-formatter with the given width.
    explicit text_formatter(size_t width);

    /**
     * Create a new-line, and write the contents of the current prefix to it.
     *
     * @see set_prefix
     */
    void newline();

    /// Write the given value to the current line.
    template <class T>
    text_formatter& operator<<(const T& v) {
        write(v, {});
        return *this;
    }

    text_formatter& operator<<(std::ostream& (&)(std::ostream&));

    /// Set the prefix to be written after each `newline()` in scope.
    template <class T>
    auto prefix(const T& v) {
        return m_prefixes(detail::text_formatter_prefix::create(v, {}));
    }

    /// Set a color in scope.
    auto color(const color::value& v) { return m_colors(v); }

    /// Colorize the current line `[from, to)` with the given color.
    void colorize(const color::value& v, size_t from, size_t to);

    /// @return The max width.
    size_t width() const;

    /// @return The current line's length.
    size_t current_line_length() const;

    friend std::ostream& operator<<(std::ostream& os, const text_formatter& t);

private:

    struct line_t {
        std::string text;
        std::map<size_t, std::list<color::code>> color_codes;
    };

    size_t m_width;
    std::vector<line_t> m_lines;

    context_list<const detail::text_formatter_prefix> m_prefixes;
    context_list<const color::value> m_colors;

    template <class T>
    void write(const T& v, const std::list<color::value>& colors) {
        write(as_string(v), colors);
    }

    template <class T>
    void write(
        const color::value::wrapper<T>& w,
        std::list<color::value> colors
    ) {
        colors.push_back(w.c);
        write(w.v, std::move(colors));
    }

    void write(const std::string&, const std::list<color::value>&);
    void write(const char*, const std::list<color::value>&);
    void write(const std::string_view&, const std::list<color::value>&);

    friend std::ostream& operator<<(std::ostream& os, const line_t& line);

};

} // namespace fp::util::console
