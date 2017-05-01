#pragma once

#include <fp/util/named_tuple.h>
#include <fp/common/source_location.h>
#include <fp/lex/attribute.h>
#include <fp/lex/token.h>

namespace fp::lex {

/// A token, it's attribute, and it's location in the source code.
NAMED_TUPLE(
    token_value,
    (token, value)(token_attribute, attribute)(source_location, source)
);

} // namespace fp::lex
