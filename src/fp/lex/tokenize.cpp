#include <fp/lex/detail/tokenizer_state.h>
#include <fp/lex/detail/tokenizers_table.h>

#include "tokenize.h"

namespace fp::lex {

token_list tokenize(const input_view& input, diagnostic_report& diagnostics) {
    token_list tokens;
    tokens.reserve(input.size());
    detail::tokenizer_state s(input, tokens, diagnostics);
    while (s.it != s.end) {
        s.start_next_token();
        detail::tokenizers_table::get(*s.it)(s);
    }
    return tokens;
}

} // namespace fp::lex
