#pragma once

#include <memory>

namespace fp::util {

/// A Boxed value is stored on the heap.
template <class T>
class box {
public:

    using value_type = T;

    template <class... Args>
    box(Args&&... args) :
        m_value(std::make_unique<T>(std::forward<Args>(args)...))
    {}

    operator const T&() const { return *m_value; }
    operator T&() { return *m_value; }

private:

    std::unique_ptr<T> m_value;

};

} // fp::util
