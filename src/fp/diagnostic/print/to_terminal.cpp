#include <cmath>
#include <vector>
#include <optional>
#include <iomanip>

#include <fp/util/match.h>
#include <fp/util/ansi/codes.h>

#include "to_terminal.h"

namespace fp::diagnostic::print {

using namespace util::ansi;

constexpr char PRIMARY_UNDERLINE        = '~';
constexpr char PRIMARY_SINGLE_UNDERLINE = '^';
constexpr char SUPPLEMENT_UNDERLINE     = '-';

static size_t line_number_width(size_t line_number) {
    size_t w = 1;
    while (line_number /= 10) { ++w; }
    return w;
}

struct sorted_source_locations {
    struct locations_in_file {
        const source_file& file;
        std::vector<const diagnostic::location*> locations;
        size_t max_line_number_width = 0;

        void add(const diagnostic::location& loc) {
            locations.push_back(&loc);
            max_line_number_width = std::max(
                max_line_number_width,
                line_number_width(loc.source_location.line_number)
            );
        }
    };

    std::vector<locations_in_file> locations_by_file;

     void set(const diagnostic::problem& problem) {
         locations_by_file.clear();

         for (const auto& loc : problem.locations()) {
             if (loc.kind == location_kind::PRIMARY) {
                 get_file(loc.source_location.file).add(loc);
             }
         }
         for (const auto& loc : problem.locations()) {
             if (loc.kind != location_kind::SUPPLEMENT) {
                 get_file(loc.source_location.file).add(loc);
             }
         }
         for (const auto& loc : problem.locations()) {
             if (loc.kind == location_kind::CONTEXTUAL) {
                 get_file(loc.source_location.file).add(loc);
             }
         }

         // sort all locations
         for (auto& [_1, locations, _2] : locations_by_file) {
             std::sort(
                 locations.begin(), locations.end(),
                 [](const auto& loc1, const auto& loc2) {
                     return loc1->source_location.chars.begin() <
                            loc2->source_location.chars.begin();
                 }
             );
         }
    }

private:
    locations_in_file& get_file(const source_file& file) {
        for (locations_in_file& f : locations_by_file) {
            if (file == f.file) { return f; }
        }
        locations_by_file.push_back({ .file = file });
        return locations_by_file.back();
    }
};

struct labeled_code {
    struct label {
        location_kind    kind;
        size_t           column_start;
        size_t           column_end;
        std::string_view text;
    };

    struct line {
        size_t                     number;
        std::string_view           content;
        std::string_view::iterator first_non_whitespace_char;
        std::string_view::iterator last_non_whitespace_char;
        std::vector<label>         labels;
    };

    std::vector<line> lines;

    void set(const sorted_source_locations::locations_in_file& file_locations) {
        lines.clear();
        for (const auto& loc : file_locations.locations) {
            const auto& sl = loc->source_location;
            for_each_line(sl, [&](auto& line) {
                if (loc->kind == location_kind::CONTEXTUAL) { return; }
                size_t column_start =
                    line.number == sl.line_number ?
                    (sl.chars.begin() - sl.line) :
                    (line.first_non_whitespace_char - line.content.begin());
                bool is_last_line = line.content.end() >= sl.chars.end();
                size_t column_end =
                    is_last_line ?
                    (sl.chars.end() - line.content.begin()) :
                    (1 + line.last_non_whitespace_char - line.content.begin());
                std::string_view text;
                if (is_last_line) { text = loc->text; }
                line.labels.push_back(label {
                    .kind         = loc->kind,
                    .column_start = column_start,
                    .column_end   = column_end,
                    .text         = text
                });
            });
        }
        // sort all labels
        for (auto& line : lines) {
            std::sort(
                line.labels.begin(), line.labels.end(),
                [](const auto& label1, const auto& label2) {
                    return label1.column_start < label1.column_start;
                }
            );
        }
    }

private:
    template <class Callback>
    void for_each_line(const source_location& location, Callback&& cb) {
        size_t line_number = location.line_number;
        source_iterator it = location.line;
        cb(get_line(line_number, it, location.file.content.end()));
        ++it;
        for (; it != location.chars.end(); ++it) {
            if (*(it - 1) == '\n') {
                ++line_number;
                cb(get_line(line_number, it, location.file.content.end()));
            }
        }
    }

    labeled_code::line& get_line(
        size_t line_number,
        source_iterator line_start,
        source_iterator file_end
    ) {
        for (labeled_code::line& line : lines) {
            if (line_number == line.number) { return line; }
        }
        source_iterator line_end = line_start;
        while (line_end != file_end && *line_end != '\n') {
            ++line_end;
        }
        source_iterator first_non_whitespace_char = line_start;
        while (first_non_whitespace_char != line_end) {
            if (!std::isspace(*first_non_whitespace_char)) { break; }
            ++first_non_whitespace_char;
        }
        source_iterator last_non_whitespace_char = line_end - 1;
        while (last_non_whitespace_char != line_start) {
            if (!std::isspace(*last_non_whitespace_char)) { break; }
            --last_non_whitespace_char;
        }
        lines.push_back(labeled_code::line {
            .number                    = line_number,
            .content                   = make_source_view(line_start, line_end),
            .first_non_whitespace_char = first_non_whitespace_char,
            .last_non_whitespace_char  = last_non_whitespace_char
        });
        return lines.back();
    }
};

static void print_gutter(
    std::ostream& os,
    size_t line_number_width,
    std::optional<size_t> line_number = std::nullopt
) {
    os << ' ' << std::setw(line_number_width);
    line_number ? os << white << *line_number : os << ' ';
    os << grey << " | ";
}

static void print_labeled_line(
    std::ostream& os,
    const labeled_code::line& line,
    size_t line_number_width
) {
    print_gutter(os, line_number_width, line.number);
    if (line.labels.empty()) {
        os << default_color << line.content;
        return;
    }

    // storing anything other than a ANSI foreground color here will not work
    // with the current code. So don't do that.
    thread_local std::vector<graphics_code> color_per_char;
    color_per_char.clear();
    color_per_char.resize(line.content.size(), default_color);

    const labeled_code::label* last_label = &line.labels.front();
    for (auto& label : line.labels) {
        if (last_label->column_end < label.column_end) {
            last_label = &label;
        }
        for (size_t i = label.column_start; i < label.column_end; ++i) {
            // do not override primary color (red)
            if (color_per_char[i] == red) { continue; }
            color_per_char[i] =
                (label.kind == location_kind::PRIMARY) ? red : cyan;
        }
    }

    os << default_color;
    graphics_code current_color = default_color;
    size_t last_print_index = 0;
    for (size_t i = 0; i < line.content.size(); ++i) {
        if (color_per_char[i] != current_color) {
            os << line.content.substr(last_print_index, i - last_print_index);
            last_print_index = i;
            os << color_per_char[i];
            current_color = color_per_char[i];
        }
    }
    os << line.content.substr(last_print_index);

    os << '\n';
    print_gutter(os, line_number_width);
    os << default_color;
    current_color = default_color;
    last_print_index = 0;
    thread_local std::string primary_underline(1, PRIMARY_UNDERLINE);
    thread_local std::string supplemental_underline(1, SUPPLEMENT_UNDERLINE);
    thread_local std::string no_underline(1, ' ');
    size_t i = 0;
    auto print_underline = [&]() {
        size_t size = i - last_print_index;
        if (current_color == red) {
            if (size == 1) {
               os << PRIMARY_SINGLE_UNDERLINE;
            } else {
                primary_underline.resize(size, PRIMARY_UNDERLINE);
                os << primary_underline;
            }
        } else if (current_color == cyan) {
            supplemental_underline.resize(size, SUPPLEMENT_UNDERLINE);
            os << supplemental_underline;
        } else {
            no_underline.resize(size, ' ');
            os << no_underline;
        }
    };

    for (; i < line.content.size(); ++i) {
        if (color_per_char[i] != current_color) {
            print_underline();
            last_print_index = i;
            os << color_per_char[i];
            current_color = color_per_char[i];
        }
    }
    if (current_color != default_color) { print_underline(); }

    if (!last_label->text.empty()) {
        os << ' ';
        os << (last_label->kind == location_kind::PRIMARY ? red : cyan);
        os << last_label->text;
    }

    thread_local std::vector<const labeled_code::label*> labels_to_print;
    labels_to_print.clear();
    for (const auto& label : line.labels) {
        if (&label == last_label || label.text.empty()) { continue; }
        labels_to_print.push_back(&label);
    }
    while (!labels_to_print.empty()) {
        os << '\n';
        print_gutter(os, line_number_width);
        size_t prev_column = 0;
        for (const auto& label : labels_to_print) {
            if (label->column_start < prev_column) { continue; }
            no_underline.resize(label->column_start - prev_column, ' ');
            os << no_underline;
            os << (label->kind == location_kind::PRIMARY ? red : cyan) << '|';
            prev_column = label->column_start + 1;
        }
        os << '\n';
        print_gutter(os, line_number_width);
        prev_column = 0;
        for (const auto& label : labels_to_print) {
            if (label->column_start < prev_column) {
                if (label == labels_to_print.back()) {
                    os << (label->kind == location_kind::PRIMARY ? red : cyan);
                    os << "-> " << label->text;
                }
                continue;
            }
            no_underline.resize(label->column_start - prev_column, ' ');
            os << no_underline;
            os << (label->kind == location_kind::PRIMARY ? red : cyan);
            if (label == labels_to_print.back()) {
                os << label->text;
            } else {
                os << '|';
            }
            prev_column = label->column_start + 1;
        }
        labels_to_print.pop_back();
    }
}

static void print_file_locations(
    std::ostream& os,
    const sorted_source_locations::locations_in_file& file_locations
) {
    const auto& [file, locations_by_line, line_number_width] = file_locations;
    os << blue << italic << file.name << italic_off <<'\n';
    thread_local labeled_code lc;
    lc.set(file_locations);

    print_gutter(os, line_number_width); os << '\n';
    size_t previous_line_number = lc.lines.front().number;
    for (const auto& line : lc.lines) {
        if (line.number - previous_line_number > 1) {
            print_gutter(os, line_number_width); os << '\n';
            os << std::setw(line_number_width) << ' ' << grey << "...\n";
            print_gutter(os, line_number_width); os << '\n';
        }
        print_labeled_line(os, line, line_number_width);
        os << '\n';
    }
    print_gutter(os, line_number_width); os << '\n';
}

void to_terminal(std::ostream& os, const diagnostic::problem& problem) {
    if (problem.severity() == severity::ERROR) {
        os << bold << red << "error: " << reset;
    } else {
        os << bold << yellow << "warning: " << reset;
    }
    os << problem.text() << "\n";

    thread_local sorted_source_locations sorted_locations;
    sorted_locations.set(problem);
    for (const auto& file_locations : sorted_locations.locations_by_file) {
        print_file_locations(os, file_locations);
    }

    os << reset << std::endl;
}

void to_terminal(std::ostream& os, const diagnostic::report& report) {
    for (const auto& error : report.errors()) { to_terminal(os, error); }
    for (const auto& warning : report.warnings()) { to_terminal(os, warning); }
}

} // namespace fp::diagnostic::print
