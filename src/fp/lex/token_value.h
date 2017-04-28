#pragma once

#include <fp/util/named_tuple.h>
#include <fp/common/source_origin.h>

#include "attribute.h"
#include "token.h"

namespace fp::lex {

/// The type of the values stored in a @ref token_list.
NAMED_TUPLE(
    token_value,
    (token, value)(token_attribute, attribute)(source_origin, origin)
);

} // namespace fp::lex
