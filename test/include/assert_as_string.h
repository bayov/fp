#pragma once

#include <boost/preprocessor/punctuation/remove_parens.hpp>

#include <fp/util/as_string.h>

#define ASSERT_AS_STRING(expected_string, value_to_ostream)\
    ASSERT_EQ((expected_string), (fp::util::as_string(value_to_ostream)))
