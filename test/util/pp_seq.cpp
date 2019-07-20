#include <gtest/gtest.h>

#include <fp/util/pp_seq.h>

#include <test-util/assert_macro_eq.h>

namespace fp::util {

#define EXAMPLE_SEQ (1)(2)(3)
#define APPEND_ZERO(n) n##0

TEST(util_pp_seq, for_each) {
    ASSERT_MACRO_EQ("10 20 30", FP_SEQ_FOR_EACH(EXAMPLE_SEQ, APPEND_ZERO));
}

TEST(util_pp_seq, transform) {
    ASSERT_MACRO_EQ("(10) (20) (30)", FP_SEQ_TRANSFORM(EXAMPLE_SEQ, APPEND_ZERO));
}

TEST(util_pp_seq, enum_) {
    ASSERT_MACRO_EQ("10, 20, 30", FP_SEQ_ENUM(EXAMPLE_SEQ, APPEND_ZERO));
}

#define EXAMPLE_TSEQ ((a, 1))((b, 2))((c, 3))
#define CONCAT_PAIR(x, y) x##y

TEST(util_pp_seq, tseq_for_each) {
    ASSERT_MACRO_EQ("a1 b2 c3", FP_TSEQ_FOR_EACH(EXAMPLE_TSEQ, CONCAT_PAIR));
}

TEST(util_pp_seq, tseq_transform) {
    ASSERT_MACRO_EQ(
        "(a1) (b2) (c3)",
        FP_TSEQ_TRANSFORM(EXAMPLE_TSEQ, CONCAT_PAIR)
    );
}

TEST(util_pp_seq, tseq_enum) {
    ASSERT_MACRO_EQ("a1, b2, c3", FP_TSEQ_ENUM(EXAMPLE_TSEQ, CONCAT_PAIR));
}

} // namespace fp::util
