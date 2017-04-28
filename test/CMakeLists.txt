package(
    gtest
    GITHUB_REPO google/googletest
    TAG release-1.8.0
    SUBDIR googletest
    LIBRARIES gtest->pthread gtest_main->gtest
)

include_directories(include)

set(
    SOURCES
    include/assert_as_string.h
    include/assert_same.h
    include/catergorized_test.h
    lex/test.cpp
    util/test_box.cpp
    util/test_enum_class.cpp
    util/test_named_tuple.cpp
    util/test_type_name.cpp
    util/test_va_args.cpp
)

add_executable(fp_test ${SOURCES})
target_link_libraries(fp_test fp)
target_use_packages(fp_test gtest LINK gtest_main)
