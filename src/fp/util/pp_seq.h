#pragma once

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/transform.hpp>

#define SEQ_APPLY_EACH_(_, MACRO, v) MACRO v

/// Apply `MACRO` on each element in the given sequence.
#define SEQ_FOR_EACH(seq, MACRO)\
    BOOST_PP_SEQ_FOR_EACH_R(1, SEQ_APPLY_EACH_, MACRO, seq)

/// Enumerate elements in the given sequence after applying `MACRO`.
#define SEQ_ENUM(seq, MACRO)\
    BOOST_PP_SEQ_ENUM(\
        BOOST_PP_SEQ_TRANSFORM_S(1, SEQ_APPLY_EACH_, MACRO, seq)\
    )
