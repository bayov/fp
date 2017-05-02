#pragma once

#include <cstdint>
#include <string>
#include <string_view>

#include <boost/range/iterator_range.hpp>

namespace fp {

/// The type representing integers in the compiler.
using integer_type = uint64_t;

/// The type representing floating-points in the compiler.
using float_type = double;

/// The type representing character in the compiler.
using char_type = char32_t;

/// Represents a symbol in a source file.
using symbol_t = char;

} // namespace namespace fp
