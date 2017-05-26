#pragma once

#include <vector>

#include <fp/util/named_tuple.h>
#include <fp/common/source_location.h>
#include <fp/lex/token_value.h>

namespace fp::lex {

/**
 * Represents a list of tokens (returned by the lexer) and their attributes.
 *
 * The token list internally stores a `token::HEAD` at its first element, which
 * can't be accessed by normal means. The only way to access it is to decrement
 * an iterator to the beginning of the list: `tokens.begin() - 1`.
 *
 * Why is this necessary? See @ref token_view.
 *
 * The token_list has a very similar interface to std::vector, where all methods
 * ignore (skip) the existence of `token::HEAD`.
 */
class token_list {

    using container_t = std::vector<token_value>;

public:

    using value_type = token_value;
    using iterator = container_t::const_iterator;
    using const_iterator = iterator;

    /**
     * Construct an empty token list.
     *
     * @param in
     *      The source input that will be used to produce the tokens.
     */
    explicit token_list(const input_view& in) {
        m_tokens.reserve(in.size() + 1);
        push_back<token::HEAD>(
            { { in.begin(), in.begin() }, in.begin(), 0, in }
        );
    }

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
        m_tokens.emplace_back(TOKEN, std::move(attr), std::move(source));
    }

    /// Append the given token with @ref no_attribute.
    void push_back(token t, source_location source) {
        m_tokens.emplace_back(t, no_attribute{}, std::move(source));
    }

    iterator begin() const { return m_tokens.begin() + 1; }
    iterator end() const { return m_tokens.end(); }

    bool empty() const { return size() == 0; }
    size_t size() const { return m_tokens.size() - 1; }

private:

    container_t m_tokens;

};

} // namespace namespace fp::lex
