#pragma once

#include <ostream>
#include <string_view>
#include <type_traits>

#include <boost/preprocessor/seq/variadic_seq_to_seq.hpp>

#include <fp/util/pp_seq.h>
#include <fp/util/print_separated.h>

namespace fp::util {

/**
 * Defines a record, which is just a simple struct with given fields, with some
 * additional functionality.
 *
 * Additional functionality:
 *  - comparison operators `==` and `!=` (field by field)
 *  - printing to std::ostream (`operator<<`)
 *
 * Additional functionality is compiled on demand (i.e., only when each of the
 * field types support it).
 *
 * Example:
 * ~~~{.cpp}
 * FP_RECORD(point, (int, x)(int, y));
 * // basically defines `struct point { int x; int y; }` with extra fluff
 *
 * point p1 { 3, 5 };
 * point p2 { .x = 3, .y = 6 };
 *
 * p1.x; // 3
 * p1.y; // 5
 *
 * p1 == p2; // false
 * --p2.y;
 * p1 == p2; // true
 *
 * std::cout << p1; // prints { x: 3, y: 5 }
 *
 * // records can be templated
 * template <class T, class U>
 * FP_RECORD(record, (T, f1)(U, f2));
 * ~~~
 */
#define FP_RECORD(class_name, fields)\
    struct class_name {\
        FP_RECORD_FIELDS_I(class_name, BOOST_PP_VARIADIC_SEQ_TO_SEQ(fields))\
    }\

/**
 * Same as FP_RECORD, but does not define the wrapping record class, allowing
 * additional extension:
 * ~~~{.cpp}
 * struct point {
 *     FP_RECORD_FIELDS(point, (int, x)(int, y));

 *     int distance(const point&) const;
 *     int norm() const;
 * };
 * // the above point is comparable and ostream-able thanks to the macro.
 * ~~~
 */
#define FP_RECORD_FIELDS(class_name, fields)\
    FP_RECORD_FIELDS_I(class_name, BOOST_PP_VARIADIC_SEQ_TO_SEQ(fields))

#define FP_RECORD_FIELD_DEFINE_I(type, name) type name;
#define FP_RECORD_FIELD_DEFINE_TYPE_I(type, name) using name##_t = type;
#define FP_RECORD_FIELD_COMPARE_I(type, name) && lhs.name == rhs.name

namespace detail {

template <class T>
struct named_record_field {
    std::string_view name;
    T& value;
    friend std::ostream& operator<<(
        std::ostream& os, const named_record_field& f
    ) {
        return os << f.name << ": " << f.value;
    }
};

template <class T>
using const_named_record_field = named_record_field<const T>;

} // namespace detail

#define FP_RECORD_FIELD_STRING_VALUE_PAIR_I(type, name)\
    , ::fp::util::detail::const_named_record_field<type> { #name, r.name }

#define FP_RECORD_COMPILE_ON_DEMAND_I(cls, return_type)\
    template <class Record>\
    friend constexpr std::enable_if_t<std::is_same_v<Record, cls>, return_type>

// NOTE: GCC currently (9.1) segfaults when applying concepts here...
#define FP_RECORD_FIELDS_I(cls, fields)\
    FP_TSEQ_FOR_EACH(fields, FP_RECORD_FIELD_DEFINE_I)\
    FP_TSEQ_FOR_EACH(fields, FP_RECORD_FIELD_DEFINE_TYPE_I)\
    \
    FP_RECORD_COMPILE_ON_DEMAND_I(cls, bool)\
    operator==(const Record& lhs, const Record& rhs) {\
        return true FP_TSEQ_FOR_EACH(fields, FP_RECORD_FIELD_COMPARE_I);\
    }\
    \
    FP_RECORD_COMPILE_ON_DEMAND_I(cls, bool)\
    operator!=(const Record& lhs, const Record& rhs) {\
        return !(*lhs == rhs);\
    }\
    \
    FP_RECORD_COMPILE_ON_DEMAND_I(cls, std::ostream&)\
    operator<<(std::ostream& os, const Record& r) {\
        os << "{ ";\
        ::fp::util::print_comma_separated(\
            os FP_TSEQ_FOR_EACH(fields, FP_RECORD_FIELD_STRING_VALUE_PAIR_I)\
        );\
        return os << " }";\
    }

} // namespace fp::util
