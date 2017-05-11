#pragma once

#include <utility>

namespace fp::util {

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
 */
template <class T>
class context_value {

    template <class U>
    struct in_scope {

        context_value& cv;
        T* previous;
        U value_in_scope;

        in_scope(context_value& c, U&& v) :
            cv(c), previous(c.m_current), value_in_scope(std::forward<U>(v))
        {
            cv.m_current = &value_in_scope;
        }

        ~in_scope() {
            cv.m_current = previous;
        }

    };

public:

    using value_type = T;

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
    T& get() { return *m_current; }
    const T& get() const { return *m_current; }
    //@}

private:

    T* m_current;

};

} // namespace fp::util
