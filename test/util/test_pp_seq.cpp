#include <fp/util/pp_seq.h>

#include <catergorized_test.h>
#include <assert_macro_eq.h>

#define TEST(what) CATEGORIZED_TEST(util, pp_seq, what)

namespace fp::util {

#define FP_UTIL_TEST_SEQ (1)(2)(3)
#define FP_UTIL_TEST_APPEND_ZERO(n) n##0

TEST(for_each) {
    ASSERT_MACRO_EQ(
        "10 20 30",
        SEQ_FOR_EACH(FP_UTIL_TEST_SEQ, FP_UTIL_TEST_APPEND_ZERO)
    );
}

TEST(transform) {
    ASSERT_MACRO_EQ(
        "(10) (20) (30)",
        SEQ_TRANSFORM(FP_UTIL_TEST_SEQ, FP_UTIL_TEST_APPEND_ZERO)
    );
}

TEST(enum_) {
    ASSERT_MACRO_EQ(
        "10, 20, 30",
        SEQ_ENUM(FP_UTIL_TEST_SEQ, FP_UTIL_TEST_APPEND_ZERO)
    );
}

#define FP_UTIL_TEST_TSEQ ((a, 1))((b, 2))((c, 3))
#define FP_UTIL_TEST_CONCAT(x, y) x##y

TEST(tseq_for_each) {
    ASSERT_MACRO_EQ(
        "a1 b2 c3",
        TSEQ_FOR_EACH(FP_UTIL_TEST_TSEQ, FP_UTIL_TEST_CONCAT)
    );
}

TEST(tseq_transform) {
    ASSERT_MACRO_EQ(
        "(a1) (b2) (c3)",
        TSEQ_TRANSFORM(FP_UTIL_TEST_TSEQ, FP_UTIL_TEST_CONCAT)
    );
}

TEST(tseq_enum) {
    ASSERT_MACRO_EQ(
        "a1, b2, c3",
        TSEQ_ENUM(FP_UTIL_TEST_TSEQ, FP_UTIL_TEST_CONCAT)
    );
}

} // fp::util
