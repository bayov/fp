#include <fp/lex/detail/tokenizer.h>

#include "tokenize.h"

namespace fp::lex {

token_list tokenize(const input& input, diagnostic_report& diagnostics) {
    return detail::tokenizer().tokenize(input_view(input), diagnostics);
}

token_list tokenize(const input_view& input, diagnostic_report& diagnostics) {
    return detail::tokenizer().tokenize(input, diagnostics);
}


} // fp::lex
