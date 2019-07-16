#pragma once

#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/transform.hpp>

//@{
/**
 * Aliases to Boost.Preprocessor sequence macros (with a simpler interface).
 *
 * ~~~{.cpp}
 * // regular sequences
 * #define SEQ (1)(2)(3)
 * #define APPEND_ZERO(n) n##0
 *
 * FP_SEQ_FOR_EACH(SEQ, APPEND_ZERO) // 10 20 30
 * FP_SEQ_TRANSFORM(SEQ, APPEND_ZERO) // (10) (20) (30)
 * FP_SEQ_ENUM(SEQ, APPEND_ZERO) // 10, 20, 30
 *
 * // tuple-sequences
 * #define TSEQ ((a, 1))((b, 2))((c, 3))
 * #define CONCAT_PAIR(first, second) first##second
 *
 * FP_TSEQ_FOR_EACH(TSEQ, CONCAT_PAIR) // a1 b2 c3
 * FP_TSEQ_TRANSFORM(TSEQ, CONCAT_PAIR) // (a1) (b2) (c3)
 * FP_TSEQ_ENUM(TSEQ, CONCAT_PAIR) // a1, b2, c3
 * ~~~
 */
#define FP_SEQ_FOR_EACH(seq, MACRO)\
    BOOST_PP_SEQ_FOR_EACH_R(1, FP_SEQ_APPLY_EACH_I, MACRO, seq)

#define FP_SEQ_TRANSFORM(seq, MACRO)\
    BOOST_PP_SEQ_TRANSFORM_S(1, FP_SEQ_APPLY_EACH_I, MACRO, seq)

#define FP_SEQ_ENUM(seq, MACRO)\
    BOOST_PP_SEQ_ENUM(FP_SEQ_TRANSFORM(seq, MACRO))

#define FP_TSEQ_FOR_EACH(seq, MACRO)\
    BOOST_PP_SEQ_FOR_EACH_R(1, FP_TSEQ_APPLY_EACH_I, MACRO, seq)

#define FP_TSEQ_TRANSFORM(seq, MACRO)\
    BOOST_PP_SEQ_TRANSFORM_S(1, FP_TSEQ_APPLY_EACH_I, MACRO, seq)

#define FP_TSEQ_ENUM(seq, MACRO)\
    BOOST_PP_SEQ_ENUM(FP_TSEQ_TRANSFORM(seq, MACRO))
//@}

#define FP_SEQ_APPLY_EACH_I(_, MACRO, v) MACRO(v)
#define FP_TSEQ_APPLY_EACH_I(_, MACRO, v) MACRO v
