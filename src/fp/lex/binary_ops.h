#pragma once

#include <boost/preprocessor/seq/variadic_seq_to_seq.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/transform.hpp>

/// A variadic-sequence of binary-ops in the language, excluding keywords.
#define FP_BINARY_OPS_NO_KEYWORDS\
    (COMMA,             ",")\
    (COLON,             ":")\
    (PERIOD,            ".")\
    (RANGE,             "..")\
    (CLOSED_RANGE,      "...")\
    (PLUS,              "+")\
    (MINUS,             "-")\
    (MUL,               "*")\
    (DIV,               "/")\
    (MOD,               "%")\
    (POW,               "**")\
    (BIT_AND,           "&")\
    (BIT_OR,            "|")\
    (XOR,               "^")\
    (LSHIFT,            "<<")\
    (RSHIFT,            ">>")\
    (ASSIGN,            "=")\
    (PLUS_ASSIGN,       "+=")\
    (MINUS_ASSIGN,      "-=")\
    (MUL_ASSIGN,        "*=")\
    (DIV_ASSIGN,        "/=")\
    (MOD_ASSIGN,        "%=")\
    (POW_ASSIGN,        "**=")\
    (BIT_AND_ASSIGN,    "&=")\
    (BIT_OR_ASSIGN,     "|=")\
    (XOR_ASSIGN,        "^=")\
    (LSHIFT_ASSIGN,     "<<=")\
    (RSHIFT_ASSIGN,     ">>=")\
    (EQ,                "==")\
    (NE,                "!=")\
    (LT,                "<")\
    (GT,                ">")\
    (LTE,               "<=")\
    (GTE,               ">=")

/// FP_BINARY_OPS_NO_KEYWORDS as a sequence of pairs.
#define FP_BINARY_OPS_NO_KEYWORDS_SEQ\
    BOOST_PP_VARIADIC_SEQ_TO_SEQ(FP_BINARY_OPS_NO_KEYWORDS)

/// Apply `MACRO` on each element in FP_BINARY_OPS_NO_KEYWORDS.
#define FP_BINARY_OPS_NO_KEYWORDS_FOR_EACH(MACRO)\
    SEQ_FOR_EACH(FP_BINARY_OPS_NO_KEYWORDS_SEQ, MACRO)

/// Enumerator FP_BINARY_OPS_NO_KEYWORDS after applying `MACRO` to each.
#define FP_BINARY_OPS_NO_KEYWORDS_ENUM(MACRO)\
    SEQ_ENUM(FP_BINARY_OPS_NO_KEYWORDS_SEQ, MACRO)

/// A variadic-sequence of binary-ops in the language (including keywords).
#define FP_BINARY_OPS\
    FP_BINARY_OPS_NO_KEYWORDS\
    (AND,       "and")\
    (AS,        "as")\
    (IN,        "in")\
    (OF,        "of")\
    (OR,        "or")

/// FP_BINARY_OPS as a sequence of pairs.
#define FP_BINARY_OPS_SEQ BOOST_PP_VARIADIC_SEQ_TO_SEQ(FP_BINARY_OPS)

/// Apply `MACRO` on each element in FP_BINARY_OPS.
#define FP_BINARY_OPS_FOR_EACH(MACRO) SEQ_FOR_EACH(FP_BINARY_OPS_SEQ, MACRO)

/// Enumerator FP_BINARY_OPS after applying `MACRO` to each.
#define FP_BINARY_OPS_ENUM(MACRO) SEQ_ENUM(FP_BINARY_OPS_SEQ, MACRO)
