#pragma once

#include <cstdint>
#include <variant>

#include <fp/util/fundamental.h>

#include "symbol.h"
#include "token.h"

namespace fp::lex {

/// The attribute attached to a token.
template <token> struct attribute { using type = void; };

/// The type that is used to store an integer literal attribute.
using integer_type = uint64_t;

/// The type that is used to store a floating-point literal attribute.
using float_type = double;

#define SPECIALIZE_ATTRIBUTE(TOKEN, base_type)\
    template <> struct attribute<token::TOKEN> : base_type {\
        using type = base_type;\
        attribute(base_type v) : base_type(std::move(v)) {}\
    }

SPECIALIZE_ATTRIBUTE(COMMENT, input_view_t);
SPECIALIZE_ATTRIBUTE(IDENTIFIER, input_view_t);
SPECIALIZE_ATTRIBUTE(INTEGER, util::fundamental<integer_type>);
SPECIALIZE_ATTRIBUTE(FLOAT, util::fundamental<float_type>);
SPECIALIZE_ATTRIBUTE(CHAR, util::fundamental<char32_t>);
SPECIALIZE_ATTRIBUTE(STRING, input_view_t);

namespace detail {

template <class TokenSequence>
struct variant_attribute {};

template <token... TOKENS>
struct variant_attribute<util::enumerator_sequence<token, TOKENS...>> {
    using type = std::variant<attribute<TOKENS>...>;
};

using variant_attribute_t =
    typename variant_attribute<util::enum_class<token>::sequence>::type;

} // detail

/// A variant over all possible @ref token @ref attribute types.
struct token_attribute : detail::variant_attribute_t {
    using detail::variant_attribute_t::variant;

    /// @return `std::get<attribute<TOKEN>>(*this)`.
    template <token TOKEN>
    const attribute<TOKEN>& as() const {
        return std::get<attribute<TOKEN>>(*this);
    }
};

} // namespace fp::lex
