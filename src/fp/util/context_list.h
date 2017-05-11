#pragma once

#include <list>

#include <boost/iterator/transform_iterator.hpp>

#include <fp/util/deref.h>

namespace fp::util {

/**
 * A simple RAII context list holder.
 *
 * It is recommended to use the WITH utility to introduce new values to the
 * context list (see example).
 *
 * @example
 *
 *      context_list<int> ns;
 *      // `n` is a context manager that stores a list of `int`s
 *
 *      // for example, printing the current values:
 *      auto print = [](auto& ns) {
 *          for (int v : ns) { std::cout << v << ' '; }
 *      }
 *
 *      // to retrieve the current value list in context, use `.get()`:
 *      print(ns); // prints ""
 *
 *      // use `.operator()` to introduce a RAII scoped value to the context
 *      WITH(ns(42)) {
 *
 *          print(ns) // prints "42 "
 *
 *          WITH(ns(11)) {
 *
 *              print(ns) // prints "42 11 "
 *
 *              WITH(ns(3)) {
 *                  print(ns) // prints "42 11 3 "
 *              }
 *
 *              print(ns) // prints "42 11 "
 *
 *          }
 *
 *          // a value can be captured by reference
 *          int x = 33;
 *          WITH(ns(x)) {
 *              print(ns) // prints "42 33 "
 *              x = 333;
 *              print(ns) // prints "42 333 "
 *          }
 *
 *          print(ns) // prints "42 "
 *
 *      }
 *
 */
template <class T>
class context_list {

    template <class U>
    struct in_scope {

        context_list& cv;
        U value_in_scope;

        in_scope(context_list& c, U&& v) :
            cv(c), value_in_scope(std::forward<U>(v))
        {
            cv.m_values.push_back(&value_in_scope);
        }

        ~in_scope() { cv.m_values.pop_back(); }

    };

    template <class It>
    using iterator_t = boost::transform_iterator<deref, It>;

public:

    using value_type = T;

#define FP_CL_IT_TYPE(it)\
    using it = iterator_t<typename std::list<T*>::it>

    FP_CL_IT_TYPE(iterator);
    FP_CL_IT_TYPE(const_iterator);
    FP_CL_IT_TYPE(reverse_iterator);
    FP_CL_IT_TYPE(const_reverse_iterator);

    context_list() = default;

    context_list(const context_list&) = delete;
    context_list(context_list&&) = delete;
    context_list& operator=(const context_list&) = delete;
    context_list& operator=(context_list&&) = delete;

    /// @return A scoped RAII-value that pushes `v` to the context list.
    template <class U>
    in_scope<U> operator()(U&& v) { return { *this, std::forward<U>(v) }; }

    //@{
    /// @return The first value in the context list.
    T& front() { return *m_values.front(); }
    const T& front() const { return *m_values.front(); }
    //@}

    //@{
    /// @return The last value in the context list.
    T& back() { return *m_values.back(); }
    const T& back() const { return *m_values.back(); }
    //@}

#define FP_CL_IT_METHODS(it, m)\
    it m() { return it(m_values.m(), deref{}); }\
    const_##it m() const { return const_##it(m_values.m(), deref{}); }\
    const_##it c##m() const { return const_##it(m_values.m(), deref{}); }

    FP_CL_IT_METHODS(iterator, begin)
    FP_CL_IT_METHODS(iterator, end)
    FP_CL_IT_METHODS(reverse_iterator, rbegin)
    FP_CL_IT_METHODS(reverse_iterator, rend)

    /// @return `true` if context list is empty.
    bool empty() const { return m_values.empty(); }

    /// @return The number of elements in the context list.
    size_t size() const { return m_values.size(); }

private:

    std::list<T*> m_values;

};

} // namespace fp::util
