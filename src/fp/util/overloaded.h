#pragma once

#include <utility>

namespace fp::util {

namespace detail {

template <class... Fs>
struct overloaded_set : Fs... {

    using Fs::operator()...;

    constexpr explicit overloaded_set(Fs&&... fs) :
        Fs(std::forward<Fs>(fs))...
    {}

};

} // namespace detail

/**
 * Given a list of function objects `fs...`, return a overloaded function object
 * using C++'s overloading rules.
 *
 * @example
 *
 *      auto f = overloaded(
 *          [](int n) { return n; }
 *          [](std::string s) { return s; }
 *      );
 *
 *      std::cout << f(5) << std::endl; // prints `5`
 *      std::cout << f("hi") << std::endl; // prints `hi`
 */
template <class... Fs>
constexpr detail::overloaded_set<Fs...> overloaded(Fs&&... fs) {
    return detail::overloaded_set<Fs...>(std::forward<Fs>(fs)...);
}

} // namespace fp::util
