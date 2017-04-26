#include <cstdlib>

#include "detail/tokenizer.h"
#include "tokenize.h"

namespace fp::lex {

token_list tokenize(const input_t& input) {
    return detail::tokenizer().tokenize(input_view_t(input));
}

token_list tokenize(const input_view_t& input) {
    return detail::tokenizer().tokenize(input);
}


} // fp::lex
