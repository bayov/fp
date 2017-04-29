#pragma once

#include <cstdint>
#include <string>
#include <variant>

#include <fp/common/types.h>
#include <fp/common/types.h>

#include "token.h"

namespace fp::lex {

/// Represents an empty attribute
struct no_attribute {};

/// The attribute attached to a token.
template <token> struct attribute { using type = no_attribute; };
template <token TOKEN> using attribute_t = typename attribute<TOKEN>::type;

template <> struct attribute<token::COMMENT>    { using type = input_view; };
template <> struct attribute<token::IDENTIFIER> { using type = input_view; };
template <> struct attribute<token::INTEGER>    { using type = integer_type; };
template <> struct attribute<token::FLOAT>      { using type = float_type; };
template <> struct attribute<token::CHAR>       { using type = char_type; };
template <> struct attribute<token::STRING>     { using type = std::string; };

namespace detail {

template<class... Ts>
struct type_set {

    template<class T>
    static constexpr bool has() { return (... || std::is_same_v<Ts, T>); }

    template<class T>
    constexpr auto operator+(T) {
        if constexpr (has<T>()) {
            return type_set<Ts...>{};
        } else {
            return type_set<Ts..., T>{};
        }
    }

    static constexpr auto dedupe() { return (type_set<>{} + ... + Ts{}); }

    using variant_t = std::variant<Ts...>;

};

template <token... TOKENS>
constexpr auto attribute_set(util::enumerator_sequence<token, TOKENS...>) {
    return type_set<attribute_t<TOKENS>...>::dedupe();
}

using variant_attribute_t =
    decltype(attribute_set(util::enum_class<token>::sequence{}))::variant_t;

} // detail

/// A variant over all possible @ref token @ref attribute types.
struct token_attribute : detail::variant_attribute_t {
    using detail::variant_attribute_t::variant;

    /// @return `std::get<attribute<TOKEN>>(*this)`.
    template <token TOKEN>
    const attribute_t<TOKEN>& as() const {
        return std::get<attribute_t<TOKEN>>(*this);
    }
};

} // namespace fp::lex
