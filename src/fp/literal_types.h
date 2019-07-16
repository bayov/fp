#pragma once

#include <cstdint>

namespace fp {

/// Represents a parsed integer literal. TODO: replace with GMP.
using integer_t = int64_t;

/// Represents a parsed real number literal. TODO: replace with MPFR.
using real_t = long double;

/// Represents a parsed character literal.
using char_t = char32_t;

} // namespace fp
