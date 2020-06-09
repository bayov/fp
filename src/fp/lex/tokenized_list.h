#pragma once

#include <vector>

#include <fp/util/vector_view.h>
#include <fp/source_code.h>

#include <fp/lex/token.h>
#include <fp/lex/attribute.h>

namespace fp::lex {

/**
 * A token with attached attribute, originating from a source location.
 *
 * When the field `dummy` is true, the token is a dummy error token that was
 * created after encountering a syntax error (useful for error recovery).
 * In this case, its attribute value is invalid and should be ignored.
 */
struct tokenized_token {
    lex::token          token;
    bool                dummy;
    lex::attribute_t    attribute;
    fp::source_location source_location;

    /**
     * Returns the attached attribute, assuming that `token == TOKEN`. If this
     * assumption is not respected, a std::bad_variant_access will be thrown.
     */
    template <lex::token TOKEN>
    const token_attribute_t<TOKEN>& get_attribute() const {
        return std::get<token_attribute_t<TOKEN>>(attribute);
    }
};

/// A list of tokenized tokens.
using tokenized_list = std::vector<tokenized_token>;

/// A reference to a section of lex::tokenized_list.
using tokenized_view = util::vector_view<tokenized_token>;

std::ostream& operator<<(std::ostream&, tokenized_view);

/// Iterator to a tokenized token in a lex::tokenized_list.
using token_iterator = tokenized_view::iterator;

/**
 * Returns the source location of a view of tokenized list.
 *
 * @throws std::invalid_argument when tokens_view is empty.
 */
source_location get_source_location(tokenized_view);

} // namespace fp::lex
