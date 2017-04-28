#pragma once

#include <boost/preprocessor/seq/variadic_seq_to_seq.hpp>

#include <fp/util/pp_seq.h>

/// A variadic-sequence of all keywords in the language.
#define FP_KEYWORDS\
    (AND,       "and")\
    (AS,        "as")\
    (BREAK,     "break")\
    (CASE,      "case")\
    (CATCH,     "catch")\
    (CLASS,     "class")\
    (CONCEPT,   "concept")\
    (CONTINUE,  "continue")\
    (DEFAULT,   "default")\
    (DO,        "do")\
    (ELSE,      "else")\
    (ENUM,      "enum")\
    (EXPORT,    "export")\
    (FOR,       "for")\
    (IF,        "if")\
    (IMPLICIT,  "implicit")\
    (IMPORT,    "import")\
    (IN,        "in")\
    (MUT,       "mut")\
    (NOT,       "not")\
    (OF,        "of")\
    (OR,        "or")\
    (RETURN,    "return")\
    (SWITCH,    "switch")\
    (THROW,     "throw")\
    (TRY,       "try")\
    (WHILE,     "while")

/// FP_KEYWORDS as a sequence of pairs.
#define FP_KEYWORDS_SEQ BOOST_PP_VARIADIC_SEQ_TO_SEQ(FP_KEYWORDS)

/// Apply `MACRO` on each element in FP_KEYWORDS.
#define FP_KEYWORDS_FOR_EACH(MACRO) SEQ_FOR_EACH(FP_KEYWORDS_SEQ, MACRO)

/// Enumerate FP_KEYWORDS after applying `MACRO` to each.
#define FP_KEYWORDS_ENUM(MACRO) SEQ_ENUM(FP_KEYWORDS_SEQ, MACRO)
