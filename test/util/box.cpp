#include <string>

#include <fp/util/box.h>

#include <catergorized_test.h>

#define TEST(what) CATEGORIZED_TEST(util, box, what)

namespace fp::util {

TEST(implicity_convertible) {
    box<std::string> b("value");
    auto take_string_ref = [](std::string&) {};
    take_string_ref(b);

    const auto& const_b = b;
    auto take_const_string_ref = [](const std::string&) {};
    take_const_string_ref(const_b);
}

TEST(copy_constructible) {
    box<int> b(42);
    box<int> b2(b);
}

} // namespace fp::util
