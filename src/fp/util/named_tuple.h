#pragma once

#include <type_traits>
#include <ostream>

#include <boost/preprocessor/seq/variadic_seq_to_seq.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/transform.hpp>
#include <boost/preprocessor/seq/enum.hpp>

#include "pp_seq.h"

/**
 * Define a named-tuple.
 *
 * Example usage:
 *
 *      NAMED_TUPLE(point, (double, x)(double, y));
 *      // basically defines `struct point { double x; double y; }`, but with
 *      // extra functionality.
 *
 * A named-tuple is a basic struct with some obvious functionality implemented,
 * including:
 *
 *      - default-constructor
 *      - constructor from convertible types
 *      - equality-comparison (`==` and `!=`)
 *      - printing to `std::ostream` (`<<`)
 *
 * A named-tuple can also be defined as a template-class:
 *
 *      template <class T>
 *      NAMED_TUPLE(point, (T, x)(T, y));
 *
 * @note
 *      The `fields` parameter is a Boost.Preprocessor variadic sequence of
 *      tuples `(type, name)`, but with omitted extra parentheses (which are
 *      restored by using BOOST_PP_VARIADIC_SEQ_TO_SEQ). Use NAMED_TUPLE_I for a
 *      version that does not restore parenthesis.
 */
#define NAMED_TUPLE(cls, fields)\
    NAMED_TUPLE_I(cls, BOOST_PP_VARIADIC_SEQ_TO_SEQ(fields))

#define NT_DEFINE_FIELD(type, name) type name;
#define NT_DEFINE_FIELD_TYPE(type, name) using BOOST_PP_CAT(name, _t) = type;
#define NT_PARAMETER(type, name) type name
#define NT_PARAM_MOVE(type, name) name(std::move(name))
#define NT_TEMPLATE_TPARAM(type, name) class T_##name
#define NT_TEMPLATE_PARAM(type, name) T_##name&& name
#define NT_PARAM_FORWARD(type, name) name(std::forward<T_##name>(name))
#define NT_COMPARE(type, name) && a.name == b.name
#define NT_PRINT_TO_OSTREAM(type, name) << #name << ": " << self.name << "; "

#define NT_COMPILE_ON_DEMAND(return_type)\
    template <class Cls>\
    friend std::enable_if_t<std::is_same_v<Cls, cls_t>, return_type>

#define NAMED_TUPLE_I(cls, fields)\
    class cls {\
    \
    private:\
    \
        using cls_t = cls;\
    \
    public:\
    \
        SEQ_FOR_EACH(fields, NT_DEFINE_FIELD)\
        SEQ_FOR_EACH(fields, NT_DEFINE_FIELD_TYPE)\
    \
        template <class Cls = cls> cls() {}\
    \
        cls(SEQ_ENUM(fields, NT_PARAMETER)) :\
            SEQ_ENUM(fields, NT_PARAM_MOVE)\
        {}\
    \
        template <SEQ_ENUM(fields, NT_TEMPLATE_TPARAM)>\
        cls(SEQ_ENUM(fields, NT_TEMPLATE_PARAM)) :\
            SEQ_ENUM(fields, NT_PARAM_FORWARD)\
        {}\
    \
        NT_COMPILE_ON_DEMAND(bool) operator==(const Cls& a, const Cls& b) {\
            return true SEQ_FOR_EACH(fields, NT_COMPARE);\
        }\
        NT_COMPILE_ON_DEMAND(bool) operator!=(const Cls& a, const Cls& b) {\
            return !(a == b);\
        }\
    \
        NT_COMPILE_ON_DEMAND(std::ostream&)\
        operator<<(std::ostream& os, const Cls& self) {\
            os << #cls << " { ";\
            os SEQ_FOR_EACH(fields, NT_PRINT_TO_OSTREAM) << '}';\
            return os;\
        }\
    \
    }
