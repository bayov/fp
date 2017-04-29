#pragma once

#include <fp/common/error.h>

namespace fp::lex {

/// Represents a lexical analysis error.
struct error : fp::error { using fp::error::error; };

} // namespace fp
