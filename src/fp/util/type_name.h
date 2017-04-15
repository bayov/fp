#pragma once

#include <string>

namespace fp::util {

/// @return A demangled C++ type name from the given mangled name.
std::string demangle(const char* name);

/// @return A demangled type name for type `T`.
template <class T>
std::string type_name() { return demangle(typeid(T).name()); }

/// @return A demangled type name for value `v`.
template <class T>
std::string type_name(const T& v) { return demangle(typeid(v).name()); }

} // fp::util
