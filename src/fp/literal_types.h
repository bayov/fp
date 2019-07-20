#pragma once

#include <cstdint>

#include <fp/source_code.h>

namespace fp {

/// Represents a parsed integer literal. TODO: replace with GMP.
using integer_t = source_view;

/// Represents a parsed real number literal. TODO: replace with MPFR.
using float_t = source_view;

/// Represents a parsed character literal.
using char_t = char32_t;

} // namespace fp
