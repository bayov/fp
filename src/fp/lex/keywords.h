#pragma once

#include <boost/preprocessor/seq/variadic_seq_to_seq.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

#define FP_KEYWORDS\
    (AND, "and")\
    (AS, "as")\
    (BREAK, "break")\
    (CASE, "case")\
    (CATCH, "catch")\
    (CLASS, "class")\
    (CONCEPT, "concept")\
    (CONTINUE, "continue")\
    (DEFAULT, "default")\
    (DO, "do")\
    (ELSE, "else")\
    (ENUM, "enum")\
    (EXPORT, "export")\
    (FOR, "for")\
    (IF, "if")\
    (IMPLICIT, "implicit")\
    (IMPORT, "import")\
    (IN, "in")\
    (MUT, "mut")\
    (NOT, "not")\
    (OF, "of")\
    (OR, "or")\
    (OVERRIDE, "override")\
    (RETURN, "return")\
    (SWITCH, "switch")\
    (THROW, "throw")\
    (TRY, "try")\
    (WHILE, "while")

#define FP_KEYWORDS_SEQ BOOST_PP_VARIADIC_SEQ_TO_SEQ(FP_KEYWORDS)

#define FP_KEYWORDS_COUNT BOOST_PP_SEQ_SIZE(FP_KEYWORDS_SEQ)

#define FP_KEYWORD_APPLY_EACH(_1, MACRO, keyword) MACRO keyword

#define FP_KEYWORDS_FOR_EACH(MACRO)\
    BOOST_PP_SEQ_FOR_EACH_R(1, FP_KEYWORD_APPLY_EACH, MACRO, FP_KEYWORDS_SEQ)
