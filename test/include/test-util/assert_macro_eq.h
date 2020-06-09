#pragma once

#define STRINGIFY_VA_ARGS_I(...) #__VA_ARGS__
#define STRINGIFY_VA_ARGS(...) STRINGIFY_VA_ARGS_I(__VA_ARGS__)

/**
 * A Google Test assertion: Verifies that the result of a preprocessor macro
 * expands to the expected string
 */
#define ASSERT_MACRO_EQ(expected_string, macro_result...)\
    ASSERT_EQ(expected_string, STRINGIFY_VA_ARGS(macro_result))
