#pragma once

//#include <fp/util/static_string_view.h>
#include <fp/source_code.h>

namespace fp::lex::detail {

/// A compile-time range of source code characters.
template <char FROM, char TO>
struct characters_range {
    static constexpr bool contain(char c) { return FROM <= c && c <= TO; }
};

/// Just like detail::characters_range, but contains one specific character.
template <char CHARACTER>
struct specific_character {
    static constexpr bool contain(char c) { return c == CHARACTER; }
};

/// Contains multiple compile-time characters ranges (detail::characters_range).
template <class... CharacterRanges>
struct composite_characters_range {
    static constexpr bool contain(char s) {
        return (... || CharacterRanges::contain(s));
    }
};

using decimal_digits    = characters_range<'0', '9'>;
using uppercase_letters = characters_range<'A', 'Z'>;
using lowercase_letters = characters_range<'a', 'z'>;

using identifier_characters = composite_characters_range<
    decimal_digits,
    uppercase_letters,
    lowercase_letters,
    specific_character<'_'>
>;

using letters = composite_characters_range<
    uppercase_letters,
    lowercase_letters
>;

} // namespace fp::lex::detail
