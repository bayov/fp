#pragma once

#include <vector>

#include <fp/util/named_tuple.h>

#include <fp/common/source_origin.h>

#include "token_value.h"

namespace fp::lex {

/// Represents a list of tokens (returned by the lexer) and their attributes.
class token_list : public std::vector<token_value> {
public:

    /// Append `TOKEN` with @ref no_attribute.
    template <token TOKEN>
    void push_back(source_origin origin) {
        static_assert(
            std::is_same_v<attribute_t<TOKEN>, no_attribute>,
            "TOKEN attribute must be `no_attribute` (empty)"
        );
        push_back<TOKEN>(std::move(origin), no_attribute{});
    }

    /// Append `TOKEN` with the given attribute.
    template <token TOKEN>
    void push_back(source_origin origin, lex::attribute_t<TOKEN> attr) {
        emplace_back(TOKEN, std::move(attr), std::move(origin));
    }

    /// Append the given token with @ref no_attribute.
    void push_back(token t, source_origin origin) {
        emplace_back(t, no_attribute{}, std::move(origin));
    }

};

} // namespace fp::lex
