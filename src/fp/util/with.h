#pragma once

#include <boost/preprocessor/cat.hpp>

#define WITH_VARIABLE_NAME() BOOST_PP_CAT(with_value_, __COUNTER__)

/**
 * Just a bit of nice syntax-sugar over RAII-style mechanisms:
 *
 * @example
 *
 *      WITH(std::lock_guard<std::mutex>(my_mutex)) {
 *          // ...
 *      }
 */
#define WITH(raii_value)\
    if (auto&& __attribute__((unused)) WITH_VARIABLE_NAME() = raii_value; true)
