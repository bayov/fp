#pragma once

#include <variant>

#include <fp/literal_types.h>
#include <fp/source_code.h>
#include <fp/lex/token.h>

namespace fp::lex {

namespace detail {

// IMPORTANT: Any new type added as an attribute here must also be added to the
//            lex::attribute variant below.
template <token> struct attr_helper               { using type = void       ; };
template <> struct attr_helper<token::COMMENT   > { using type = source_view; };
template <> struct attr_helper<token::IDENTIFIER> { using type = source_view; };
template <> struct attr_helper<token::INTEGER   > { using type = integer_t  ; };
template <> struct attr_helper<token::REAL      > { using type = real_t     ; };
template <> struct attr_helper<token::CHAR      > { using type = char_t     ; };
template <> struct attr_helper<token::STRING    > { using type = std::string; };

} // namespace detail

/**
 * Represents a lex::token's attribute type.
 *
 * The tokenizer attaches an attribute to each parsed token (for example, a
 * token::INTEGER is attached with an fp::integer_type attribute that holds the
 * actual integer's value).
 *
 * Most tokens have no attributes to them, and so their attribute will be void.
 */
template <token TOKEN>
using token_attribute_t = typename detail::attr_helper<TOKEN>::type;

/// The attribute value of a lex::token (see lex::token_attribute_t).
using attribute = std::variant<
    std::monostate, source_view, integer_t, real_t, char_t, std::string
>;

} // namespace fp::lex
