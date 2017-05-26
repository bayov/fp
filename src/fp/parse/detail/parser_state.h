#pragma once

#include <fp/util/context_value.h>
#include <fp/common/diagnostic_report.h>
#include <fp/lex/token_view.h>
#include <fp/ast/node.h>
#include <fp/parse/detail/precedence.h>

namespace fp::parse::detail {

/// The internal state of a fp::parse::detail::parser.
class parser_state {
public:

    /// A parse function to recursively process tokens.
    using parse_func = ast::node(&)(parser_state&, precedence_t);

    lex::token_iterator it;     ///< The current token.
    lex::token_iterator end;    ///< The end of the input.

    parser_state(
        const lex::token_view& tokens,
        parse_func parse,
        diagnostic_report& diagnostics
    ) :
        it(tokens.begin()),
        end(tokens.end()),
        m_parse(parse),
        m_diagnostics(diagnostics)
    {}

    /// Report a diagnostic error with the current token.
    void error(std::string what = "Invalid token") {
        error(it, it + 1, std::move(what));
    }

    /// Throw an error with the tokens `[from, to)`.
    void error(
        lex::token_iterator from,
        lex::token_iterator to,
        std::string what = "Invalid token"
    ) {
        report(diagnostic::error(location(from, to), std::move(what)));
    }

    /// Report the given diagnostic.
    void report(diagnostic d) {
        if (m_ignore_diagnostics.get()) { return; }
        m_diagnostics.report(std::move(d));
    }

    /// Ignore all reported diagnostics in scope.
    auto ignore_diagnostics_in_scope() { return m_ignore_diagnostics(true); }

    /**
     * @return
     *      The source location of the current token, or the end of the input
     *      if at past the end token.
     */
    source_location location() {
        return location(it, it == end ? end : it + 1);
    }

    /// @return The source location of the tokens `[from, to)`.
    source_location location(lex::token_iterator from, lex::token_iterator to) {
        return lex::token_view(from, to);
    }

    /// @return An AST node produced from recursively parsing the input tokens.
    ast::node parse(precedence_t p) { return m_parse(*this, p); }

    /// @return `true` if the current token is `TOKEN`.
    template <lex::token TOKEN>
    bool it_is() { return it != end && it->value == TOKEN; }

private:

    parse_func m_parse;
    diagnostic_report& m_diagnostics;

    util::context_value<bool, bool> m_ignore_diagnostics =
        util::context_value<bool>::with(false);

};

} // namespace fp::parse::detail
