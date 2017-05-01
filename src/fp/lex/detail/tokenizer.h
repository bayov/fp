#pragma once

#include <deque>

#include <fp/util/constexpr_table.h>
#include <fp/common/diagnostic_report.h>
#include <fp/lex/detail/tokenizer_state.h>
#include <fp/lex/detail/tokenizers_table.h>

namespace fp::lex::detail {

/// Producer of tokens from input symbols.
struct tokenizer {

    inline token_list tokenize(
        const input_view& input,
        diagnostic_report& diagnostics
    ) {
        token_list tokens;
        tokens.reserve(input.size());
        tokenizer_state s(input, tokens, diagnostics);
        while (s.it != s.end) {
            s.start_next_token();
            tokenizers_table::get(*s.it)(s);
        }
        return tokens;
    }

};

} // fp::lex::detail
