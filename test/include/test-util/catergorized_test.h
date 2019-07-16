#pragma once

#define GTEST_DONT_DEFINE_TEST 1
#include <gtest/gtest.h>
#undef GTEST_DONT_DEFINE_TEST

#define CATEGORIZED_TEST(package, subject, test_name)\
    GTEST_TEST(package##__##subject, test_name)
