#pragma once

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/transform.hpp>
#include <boost/preprocessor/seq/enum.hpp>

#define SEQ_APPLY_EACH_(_, MACRO, v) MACRO(v)

/**
 * @example
 *
 *      #define SEQ (1)(2)(3)
 *      #define APPEND_ZERO(n) n##0
 *
 *      SEQ_FOR_EACH(SEQ, APPEND_ZERO) // 10 20 30
 */
#define SEQ_FOR_EACH(seq, MACRO)\
    BOOST_PP_SEQ_FOR_EACH_R(1, SEQ_APPLY_EACH_, MACRO, seq)

/**
 * @example
 *
 *      #define SEQ (1)(2)(3)
 *      #define APPEND_ZERO(n) n##0
 *
 *      SEQ_TRANSFORM(SEQ, APPEND_ZERO) // (10) (20) (30)
 */
#define SEQ_TRANSFORM(seq, MACRO)\
    BOOST_PP_SEQ_TRANSFORM_S(1, SEQ_APPLY_EACH_, MACRO, seq)

/**
 * @example
 *
 *      #define SEQ (1)(2)(3)
 *      #define APPEND_ZERO(n) n##0
 *
 *      SEQ_ENUM(SEQ, APPEND_ZERO) // 10, 20, 30
 */
#define SEQ_ENUM(seq, MACRO) BOOST_PP_SEQ_ENUM(SEQ_TRANSFORM(seq, MACRO))

#define TSEQ_APPLY_EACH_(_, MACRO, v) MACRO v

/**
 * @example
 *
 *      #define TSEQ ((a, 1))((b, 2))((c, 3))
 *      #define CONCAT(x, y) x##y
 *
 *      TSEQ_FOR_EACH(TSEQ, CONCAT) // a1 b2 c3
 */
#define TSEQ_FOR_EACH(seq, MACRO)\
    BOOST_PP_SEQ_FOR_EACH_R(1, TSEQ_APPLY_EACH_, MACRO, seq)

/**
 * @example
 *
 *      #define TSEQ ((a, 1))((b, 2))((c, 3))
 *      #define CONCAT(x, y) x##y
 *
 *      TSEQ_TRANSFORM(TSEQ, CONCAT) // (a1)(b2)(c3)
 */
#define TSEQ_TRANSFORM(seq, MACRO)\
    BOOST_PP_SEQ_TRANSFORM_S(1, TSEQ_APPLY_EACH_, MACRO, seq)

/**
 * @example
 *
 *      #define TSEQ ((a, 1))((b, 2))((c, 3))
 *      #define CONCAT(x, y) x##y
 *
 *      TSEQ_TRANSFORM(TSEQ, CONCAT) // a1, b2, c3
 */
#define TSEQ_ENUM(seq, MACRO) BOOST_PP_SEQ_ENUM(TSEQ_TRANSFORM(seq, MACRO))
