#pragma once

#include <vector>

#include <fp/util/named_tuple.h>

#include <fp/common/source_location.h>

#include "token_value.h"

namespace fp::lex {

/// Represents a list of tokens (returned by the lexer) and their attributes.
class token_list : public std::vector<token_value> {
public:

    /// Append `TOKEN` with @ref no_attribute.
    template <token TOKEN>
    void push_back(source_location source) {
        static_assert(
            std::is_same_v<attribute_t<TOKEN>, no_attribute>,
            "TOKEN attribute must be `no_attribute` (empty)"
        );
        push_back<TOKEN>(std::move(source), no_attribute{});
    }

    /// Append `TOKEN` with the given attribute.
    template <token TOKEN>
    void push_back(source_location source, lex::attribute_t<TOKEN> attr) {
        emplace_back(TOKEN, std::move(attr), std::move(source));
    }

    /// Append the given token with @ref no_attribute.
    void push_back(token t, source_location source) {
        emplace_back(t, no_attribute{}, std::move(source));
    }

};

} // namespace fp::lex
