#pragma once

#include <string>

namespace fp::util {

/// Returns a demangled C++ type name from the given mangled `name`.
std::string demangle(const char* name);

/// Returns a demangled type name for type `T`.
template <class T>
std::string type_name() { return demangle(typeid(T).name()); }

namespace detail { template <class> struct qualified_type_name_box {}; }

/// Returns a qualified type name for type `T`.
template <class T>
std::string qualified_type_name() {
    std::string name = type_name<detail::qualified_type_name_box<T>>();
    name.erase(0, sizeof("fp::util::detail::qualified_type_name_box"));
    name.erase(name.size() - 1);
    return name;
}

/// Returns a demangled type name for value `v`.
template <class T>
std::string type_name(const T& v) { return demangle(typeid(v).name()); }

} // namespace fp::util
