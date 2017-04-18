#pragma once

#include <vector>

#include <fp/util/named_tuple.h>

#include "attribute.h"
#include "token.h"
#include "token_source.h"

namespace fp::lex {

/// The type of the values stored in a @ref token_list.
NAMED_TUPLE(
    token_list_value,
    (token, value)(token_attribute, attribute)(token_source, source)
);

/// Represents a list of tokens (returned by the lexer) and their attributes.
class token_list : public std::vector<token_list_value> {
public:

    /// @return `at(pos).value`
    token value_at(size_t pos) const { return at(pos).value; }

    /// @return `at(pos).attribute`
    const token_attribute& attribute_at(size_t pos) const {
        return at(pos).attribute;
    }

    /// @return `at(pos).source`
    const token_source& source(size_t pos) const { return at(pos).source; }

    /// Append `TOKEN` with @ref no_attribute.
    template <token TOKEN>
    void push_back(token_source source) {
        static_assert(
            std::is_same_v<attribute_t<TOKEN>, no_attribute>,
            "TOKEN attribute must be `no_attribute` (empty)"
        );
        push_back<TOKEN>(std::move(source), no_attribute{});
    }

    /// Append `TOKEN` with the given attribute.
    template <token TOKEN>
    void push_back(token_source source, lex::attribute_t<TOKEN> attr) {
        emplace_back(TOKEN, std::move(attr), std::move(source));
    }

    /// Append the given token with @ref no_attribute.
    void push_back(token t, token_source source) {
        emplace_back(t, no_attribute{}, std::move(source));
    }

};

} // namespace fp::lex
