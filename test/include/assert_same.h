#pragma once

#include <boost/preprocessor/punctuation/remove_parens.hpp>

#include <fp/util/type_name.h>

#define ASSERT_SAME(type1, type2)\
    ASSERT_EQ(\
        (fp::util::type_name< BOOST_PP_REMOVE_PARENS(type1)>()),\
        (fp::util::type_name< BOOST_PP_REMOVE_PARENS(type2)>())\
    )
