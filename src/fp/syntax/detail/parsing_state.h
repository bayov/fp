#pragma once

#include <fp/diagnostic/report.h>
#include <fp/lex/tokenized_list.h>
#include <fp/syntax/ast/node.h>
#include <fp/syntax/detail/precedence.h>

namespace fp::syntax::detail {

/// The internal state being kept during syntax parsing.
struct parsing_state {
    /// A parse function to recursively process tokens.
    using parse_function_t = ast::node (&)(parsing_state&, precedence_t);

    lex::token_iterator next; ///< Points to the next token in the input.
    lex::token_iterator end;  ///< Points to the end of the input.

    parsing_state(
        lex::tokenized_view tokens,
        parse_function_t parse,
        diagnostic::report& report
    ) :
        next(tokens.begin()),
        end(tokens.end()),
        parse_(parse),
        report_(report)
    {}

    /// Reports a diagnostic::error for the next token.
//    diagnostic::problem& report_error(std::string text = "Invalid token") {
//        ...
//    }

    /// Reports a diagnostic::error with the given `text`.
    diagnostic::problem& report_error(std::string text) {
         report_problem(diagnostic::error(std::move(text)));
         return report_.errors().back();
    }

    /// Reports the given diagnostic::problem.
    void report_problem(diagnostic::problem p) {
//        if (m_ignore_diagnostics.get()) { return; }
        report_.add(std::move(p));
    }

    /// Ignore all reported diagnostics in scope.
//    auto ignore_diagnostics_in_scope() { return m_ignore_diagnostics(true); }

    /**
     * Returns the source location of the next token, or the end of the input
     * if there's no next token.
     */
    source_location location() {
        return location(next, next == end ? end : next + 1);
    }

    /// Returns the source location of the tokens `[from, to)`.
    static source_location location(
        lex::token_iterator from,
        lex::token_iterator to
    ) {
        return lex::get_source_location(lex::tokenized_view(from, to));
    }

    /**
     * Returns an AST node produced from recursively parsing the next input
     * tokens.
     *
     * Parsing of infix and postfix operators will continue until encountering
     * a token whose precedence is lower-than or equal-to `p` (see
     * detail::precedence_table).
     */
    ast::node parse(precedence_t p) { return parse_(*this, p); }

    /// Returns `true` if the next token is `TOKEN`.
    bool next_is(lex::token t) { return next != end && next->token == t; }

private:
    parse_function_t parse_;

    /// Any problems encountered during parsing is reported here.
    diagnostic::report& report_;

//    util::context_value<bool, bool> m_ignore_diagnostics =
//        util::context_value<bool>::with(false);

};

} // namespace fp::syntax::detail
