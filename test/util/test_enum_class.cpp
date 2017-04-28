#include <fp/util/enum_class.h>

#include <catergorized_test.h>
#include <assert_same.h>

#define TEST(what) CATEGORIZED_TEST(util, enum_class, what)

namespace fp::util {

ENUM_CLASS(suit, uint8_t, DIAMONDS, CLUBS, HEARTS, SPADES);

TEST(name) { ASSERT_EQ("suit", enum_class<suit>::name); }

TEST(underlying_type) {
    ASSERT_SAME(uint8_t, enum_class<suit>::underlying_type);
}

TEST(size) { ASSERT_EQ(4, enum_class<suit>::size); }

TEST(sequence) {
    ASSERT_SAME(
        (
            enumerator_sequence<
                suit, suit::DIAMONDS, suit::CLUBS, suit::HEARTS, suit::SPADES
            >
        ),
        enum_class<suit>::sequence
    );
}

TEST(compile_time_traits) {
    ASSERT_EQ(2, enumerator<suit::HEARTS>::index);
    ASSERT_EQ("HEARTS", enumerator<suit::HEARTS>::name);
}

TEST(run_time_traits) {
    suit clubs = suit::CLUBS;
    ASSERT_EQ(1, info(clubs).index());
    ASSERT_EQ("CLUBS", info(clubs).name());
    ASSERT_EQ(suit::CLUBS, info(clubs).value());
}

} // fp::util
