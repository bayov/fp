#pragma once

#include <cstdint>
#include <string>
#include <variant>

#include "symbol.h"
#include "token.h"

namespace fp::lex {

/// Represents an empty attribute
struct no_attribute {};

/// The attribute attached to a token.
template <token> struct attribute { using type = no_attribute; };
template <token TOKEN> using attribute_t = typename attribute<TOKEN>::type;

template <> struct attribute<token::COMMENT> { using type = input_view_t; };
template <> struct attribute<token::IDENTIFIER> { using type = input_view_t; };
template <> struct attribute<token::INTEGER> { using type = uint64_t; };
template <> struct attribute<token::FLOAT> { using type = double; };
template <> struct attribute<token::CHAR> { using type = char32_t; };
template <> struct attribute<token::STRING> { using type = std::string; };

namespace detail {

template<class... Types> struct type_set;

/// `::value` is true if `TypeSet` contains `T`.
template <class TypeSet, class T> struct type_set_has;

template <class... Types, class T>
struct type_set_has<type_set<Types...>, T> {
    static constexpr bool value = (... || std::is_same_v<Types, T>);
};

/// Pushes `T` to the given `TypeSet` (if it is not already in it).
template <class TypeSet, class T, bool IN = type_set_has<TypeSet, T>::value>
struct type_set_push;

template <class... Types, class T>
struct type_set_push<type_set<Types...>, T, false> {
    using type = type_set<Types..., T>;
};

template <class TypeSet, class T>
struct type_set_push<TypeSet, T, true> { using type = TypeSet; };

/// Given a list of types, return a @ref type_set with no duplicates.
template <class... Types> struct make_type_set;

template <class T, class... Types>
struct make_type_set<T, Types...> {
    using type = typename type_set_push<
        typename make_type_set<Types...>::type, T
    >::type;
};

template <class T>
struct make_type_set<T> { using type = type_set<T>; };

template <class TokenSequence>
struct variant_attribute;

template <token... TOKENS>
struct variant_attribute<util::enumerator_sequence<token, TOKENS...>> {
    using type = typename variant_attribute<
        typename make_type_set<attribute_t<TOKENS>...>::type
    >::type;
};

template <class... AttributeTypes>
struct variant_attribute<type_set<AttributeTypes...>> {
    using type = std::variant<AttributeTypes...>;
};

using variant_attribute_t =
    typename variant_attribute<util::enum_class<token>::sequence>::type;

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
