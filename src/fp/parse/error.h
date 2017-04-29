#pragma once

#include <fp/common/error.h>

#include <fp/lex/token_view.h>

namespace fp::parse {

/// Represents a parser error.
class error : public fp::error {
public:

    error(std::string what, lex::token_view tokens) :
        fp::error(std::move(what), tokens),
        m_tokens(std::move(tokens))
    {}

    /// The erroneous tokens.
    const lex::token_view& tokens() const { return m_tokens; }

private:

    lex::token_view m_tokens;

};

} // namespace fp::parse
