#include <cstdlib>

#include "detail/tokenizer.h"
#include "tokenize.h"

namespace fp::lex {

token_list tokenize(const input& input) {
    return detail::tokenizer().tokenize(input_view(input));
}

token_list tokenize(const input_view& input) {
    return detail::tokenizer().tokenize(input);
}


} // fp::lex
