#pragma once

#include <utility>

namespace fp::util {

namespace detail {

template <class T, class TopScopeT>
struct context_value_storage {

    TopScopeT in_top_scope;
    T* current;

    explicit context_value_storage(TopScopeT&& v) :
        in_top_scope(std::forward<TopScopeT>(v)),
        current(&in_top_scope)
    {}

};

template <class T>
struct context_value_storage<T, void> { T* current; };

} // namespace detail

/**
 * A simple RAII context value holder.
 *
 * It is recommended to use the WITH utility to introduce new context scopes
 * (see example).
 *
 * @example
 *
 *      context_value<int> n;
 *      // `n` is a context manager that stores an `int`
 *
 *      // to retrieve the current value in context, use `.get()`:
 *      n.get();  <-- undefined behaviour, since no value is in context!
 *
 *      // use `.operator()` to introduce a RAII scoped value to the context
 *      WITH(n(42)) {
 *
 *          std::cout << n.get() << std::endl; // prints 42
 *
 *          WITH(n(11)) {
 *
 *              std::cout << n.get() << std::endl; // prints 11
 *
 *          } // `11` goes out of scope, previous context value is restored
 *
 *          std::cout << n.get() << std::endl; // prints 42
 *
 *          // a value can be captured by reference
 *          int x = 33;
 *          WITH(n(x)) {
 *              std::cout << n.get() << std::endl; // prints 33
 *              x = 333;
 *              std::cout << n.get() << std::endl; // prints 333
 *          }
 *
 *          std::cout << n.get() << std::endl; // prints 42
 *
 *      }
 *
 *      // to create a context value with a value in top scope, use `::with`
 *      auto n = context_value<int>::with(5); // 5 is captured by value
 *      auto n = context_value<int>::with(x); // x is captured by reference
 *
 */
template <class T, class TopScopeT = void>
class context_value {

    template <class U>
    struct in_scope {

        context_value& cv;
        T* previous;
        U value_in_scope;

        in_scope(context_value& c, U&& v) :
            cv(c),
            previous(c.m_storage.current),
            value_in_scope(std::forward<U>(v))
        {
            cv.m_storage.current = &value_in_scope;
        }

        ~in_scope() { cv.m_storage.current = previous; }

    };

public:

    using value_type = T;

    template <class U>
    static context_value<T, U> with(U&& v) {
        return context_value<T, U>(std::forward<U>(v));
    }

    context_value() = default;

    context_value(const context_value&) = delete;
    context_value(context_value&&) = delete;
    context_value& operator=(const context_value&) = delete;
    context_value& operator=(context_value&&) = delete;

    /// @return A scoped RAII-value that sets `v` to the current context.
    template <class U>
    in_scope<U> operator()(U&& v) { return { *this, std::forward<U>(v) }; }

    //@{
    /// @return The current value in context.
    T& get() { return *m_storage.current; }
    const T& get() const { return *m_storage.current; }
    //@}

private:

    detail::context_value_storage<T, TopScopeT> m_storage;

    /// Construct the context value with `v` in the top context.
    template <class U = TopScopeT, class = std::enable_if_t<!std::is_void_v<U>>>
    explicit context_value(U&& v) : m_storage(std::forward<U>(v)) {}

    template <class, class>
    friend class context_value;

};

} // namespace fp::util
