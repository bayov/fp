#pragma once

#include <optional>

namespace fp::util {

/**
 * Represents value of type `T` that depends on a "context".
 *
 * ~~~{.cpp}
 * context_value<int> n(42);
 * assert(n.get() == 42);
 * FP_WITH(n = 11) {
 *     assert(n.get() == 11);
 *     FP_WITH(n = 5) { assert(n.get() == 5); }
 *     assert(n.get() == 11); // 11 is restored
 * }
 * assert(n.get() == 42); // 42 is restored
 * ~~~
 *
 * As can be seen in the example above, context_value enables a variable `n` to
 * be assigned with a a new value for the duration of a scope. When it goes out
 * of scope, the original value is restored.
 *
 * TODO: Add a reference to an API that uses context_value, showing its usage
 *       and usefulness.
 *
 * Base Types
 * ----------
 * Note that there's no need to explicitly tell a context_value to store
 * references, as it works by way of its implementation:
 * ~~~{.cpp}
 * context_value<std::ostream> output_stream(std::cout);
 *
 * // `output_stream` internally stores a pointer (`std::ostream*`), so anything
 * // that can be implicitly converted as a pointer to it can be set in scope
 * FP_WITH(output_stream = std::ofstream("/tmp/out.txt")) { ... }
 * ~~~
 *
 * Omitting Initial Value
 * ----------------------
 * The initial value can be omitted, but then accessing the context value
 * without an explicit context is undefined-behaviour:
 * ~~~{.cpp}
 * context_value<int> n;
 *
 * n.get(); // undefined-behaviour: `n` has no value in this context
 * FP_WITH(n = 42) { ... } // good, `n` now has a value in context
 * ~~~
 *
 * Iterating Over All Contexts
 * ---------------------------
 * It is possible to iterate over all available contexts available, effectively
 * turning the usage of the context-value into a "context-list":
 * ~~~{.cpp}
 * context_value<int> n;
 *
 * auto print = [&]() {
 *     for (int x : n) { std::cout << x << " "; }
 * };

 * FP_WITH(n = 42) {
 *     FP_WITH(n = 11) {
 *         FP_WITH(n = 5) {
 *             print(); // prints "42 11 5 "
 *         }
 *         print(); // prints "42 11 "
 *     }
 *     print(); // prints "42 "
 * }
 * print(); // prints ""
 * ~~~
 */
template <class T>
struct context_value {
private:
    struct node;
    template <class> struct context;

public:
    using value_type = T;
    struct iterator;

    context_value() = default;

    template <class U>
    explicit context_value(U&& initial_value) :
        initial_value(std::in_place, *this, std::forward<U>(initial_value))
    {}

    context_value(const context_value&)     = delete;
    context_value(context_value&&)          = delete;
    context_value& operator=(context_value) = delete;

    template <class ScopeT>
    context<ScopeT> operator=(ScopeT&& value) {
        return {*this, std::forward<ScopeT>(value)};
    }

    T& get() const { return *current_value; }

    iterator begin() const { return iterator(first_context_node); }
    iterator   end() const { return iterator(nullptr           ); }

private:
    /**
     * Points the value in the current context. This pointer is dereferenced
     * whenever an access is made (through context_value::get).
     *
     * This pointer is the same as `current_context_node.value_pointer`, and so
     * it might seem it should exist, but it is here so that the overhead of
     * accessing a context_value is a single pointer-dereference, and not two.
     */
    T* current_value = nullptr;

    /// Points to the topmost context node, and null if there's none such.
    node* first_context_node   = nullptr;
    node* current_context_node = nullptr;

    /// Only used when context_value is constructed with an initial-value.
    std::optional<context<T>> initial_value;

    struct node {
        context_value& cv;
        T* value;
        node* prev;
        node* next;

        node(context_value& cv, T* v) :
            cv(cv),
            value(v),
            prev(cv.current_context_node),
            next(nullptr)
        {
            if (prev) { prev->next = this; }
            cv.current_value = v;
            cv.current_context_node = this;
            if (!cv.first_context_node) { cv.first_context_node = this; }
        }

        ~node() {
            if (prev) {
                // it's guaranteed that context_nodes will be destructed from
                // last to first, so we can safely assume our `next` pointer is
                // null here
                prev->next = nullptr;
                cv.current_value = prev->value;
                cv.current_context_node  = prev;
            } else {
                // this is the topmost context node
                cv.current_value         = nullptr;
                cv.first_context_node    = nullptr;
                cv.current_context_node  = nullptr;
            }
        }

        node(const node&)     = delete;
        node(node&&)          = delete;
        node& operator=(node) = delete;
    };

    template <class U>
    struct context {
        U    value;
        node node_;

        context(context_value& cv, U&& v) :
            value(std::forward<U>(v)),
            node_(cv, &value)
        {}
    };

public:
    struct iterator {
        using iterator_category = std::input_iterator_tag;
        using value_type        = T;
        using difference_type   = ssize_t;
        using pointer           = const T*;
        using reference         = const T&;

        explicit iterator(node* n) : n(n) {}

        const T& operator*() const { return *n->value; }

        iterator& operator++() { n = n->next; return *this; }

        bool operator==(const iterator& other) const { return n == other.n; }
        bool operator!=(const iterator& other) const { return n != other.n; }

    private:
        node* n;
    };
};

} // namespace fp::util
