#pragma once

#include <boost/preprocessor/punctuation/remove_parens.hpp>

#include <fp/util/type_name.h>

/// Assert that `std::is_same_v<type1, type2>` (with nicer reporting of types).
#define ASSERT_TYPE_EQ(type1, type2)\
    ASSERT_EQ(\
        (::fp::util::qualified_type_name<BOOST_PP_REMOVE_PARENS(type1)>()),\
        (::fp::util::qualified_type_name<BOOST_PP_REMOVE_PARENS(type2)>())\
    )
