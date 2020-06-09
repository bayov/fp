#pragma once

namespace fp::util {

/**
 * Given a list of function objects `Fs...`, return an overloaded function
 * object using C++'s overloading rules.
 *
 * ~~~{.cpp}
 * auto f = overloaded {
 *     [](int n) { return n; }
 *     [](std::string s) { return s; }
 * };
 *
 * std::cout << f(5)    << std::endl; // prints `5`
 * std::cout << f("hi") << std::endl; // prints `hi`
 * ~~~
 */
template<class... Fs> struct overloaded : Fs... { using Fs::operator()...; };
template<class... Fs> overloaded(Fs...) -> overloaded<Fs...>;

} // namespace fp::util
