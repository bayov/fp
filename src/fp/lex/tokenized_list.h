#pragma once

#include <ostream>
#include <vector>

#include <fp/util/record.h>
#include <fp/util/vector_view.h>
#include <fp/source_code.h>

#include <fp/lex/token.h>
#include <fp/lex/attribute.h>

namespace fp::lex {

/// A token with attached attribute, originating from a source location.
FP_RECORD(tokenized_token,
    (lex::token         , token    )
    (lex::attribute_t   , attribute)
    (fp::source_location, source_location)
);

std::ostream& operator<<(std::ostream&, const tokenized_token&);

/// A list of tokenized tokens.
using tokenized_list = std::vector<tokenized_token>;

/// A reference to a section of lex::tokenized_list.
using tokenized_view = util::vector_view<tokenized_token>;

/// Iterator to a tokenized token in a lex::tokenized_list.
using token_iterator = tokenized_view::iterator;

/**
 * Returns the source location of a view of tokenized list.
 *
 * @throws std::invalid_argument when tokens_view is empty.
 */
source_location get_source_location(tokenized_view);

} // namespace fp::lex
