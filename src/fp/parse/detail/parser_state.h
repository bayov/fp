#pragma once

#include <fp/lex/token_view.h>

#include <fp/ast/node.h>

#include <fp/parse/error.h>

namespace fp::parse::detail {

class parser;

/// The internal state of a fp::parse::detail::parser.
class parser_state {
public:

    lex::token_iterator it;     ///< The current token.
    lex::token_iterator end;    ///< The end of the input.

    explicit parser_state(parser&);

    void initialize(const lex::token_view& tokens);

    ast::node parse();

    /// Throw an error with the current token being parsed.
    void error(std::string what = "Invalid token") const;

    /// Throw an error with the tokens `[from, to)`.
    void error(
        lex::token_iterator from,
        lex::token_iterator to,
        std::string what = "Invalid token"
    ) const;

private:

    parser& m_parser;

};

} // fp::parse::detail
