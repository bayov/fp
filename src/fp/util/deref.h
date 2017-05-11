#pragma once

namespace fp::util {

/// Function object that dereferences its operand (using `operator*`).
struct deref {
    template <class T>
    decltype(auto) operator()(T&& v) const { return *v; }
};

} // namespace fp::util
