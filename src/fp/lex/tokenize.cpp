#include <fp/lex/detail/tokenization_state.h>
#include <fp/lex/detail/tokenizers_table.h>

#include "tokenize.h"

namespace fp::lex {

tokenized_list tokenize(source_view source, diagnostic::report& report) {
    tokenized_list tokens;

    // reserve half the source size for tokens (is a factor of 0.5 good?)
    tokens.reserve(source.size() / 2);

    detail::tokenization_state s(source, tokens, report);
    while (s.next != s.end) {
        s.begin_next_token();
        detail::tokenizers_table[*s.next](s);
    }

    return tokens;
}

} // namespace fp::lex
