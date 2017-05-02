#include "input.h"

namespace fp {

input_view::input_view(iterator begin, iterator end) :
    basic_string_view(&*begin, end - begin)
{}

input_view::input_view(const input& in) :
    basic_string_view(&in.front(), in.size())
{}

} // namespace fp
