#include <fp/util/with.h>
#include <fp/util/context_list.h>

#include <catergorized_test.h>

#define TEST(what) CATEGORIZED_TEST(util, context_list, what)

namespace fp::util {

template <class T>
std::list<T> as_list(const context_list<T>& cl) {
    return { cl.begin(), cl.end() };
}

TEST(basic_usage) {
    context_list<int> ns;
    WITH(ns(42)) {
        ASSERT_EQ(std::list<int>({ 42 }), as_list(ns));
        WITH(ns(11)) { ASSERT_EQ(std::list<int>({ 42, 11 }), as_list(ns)); }
        ASSERT_EQ(std::list<int>({ 42 }), as_list(ns));
    }
}

TEST(capture_by_reference) {
    context_list<int> ns;
    int x = 33;
    WITH(ns(x)) {
        ASSERT_EQ(std::list<int>({ 33 }), as_list(ns));
        x = 333;
        ASSERT_EQ(std::list<int>({ 333 }), as_list(ns));
    }
}

} // namespace fp::util
