#include "source_code.h"

namespace fp {

source_location merge(
    const source_location& first,
    const source_location& second
) {
    source_location merged = first;
    size_t count = second.chars.end() - first.chars.begin();
    merged.chars = source_view(first.chars.begin(), count);
    return merged;
}

} // namespace namespace fp
