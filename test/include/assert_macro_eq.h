#pragma once

#define STRINGIZE_VA_ARGS(...) STRINGIZE_VA_ARGS_I(__VA_ARGS__)
#define STRINGIZE_VA_ARGS_I(...) #__VA_ARGS__

#define ASSERT_MACRO_EQ(expected_string, macro_result...)\
    ASSERT_EQ(expected_string, STRINGIZE_VA_ARGS(macro_result))
