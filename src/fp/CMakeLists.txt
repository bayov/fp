set(
    SOURCES
    lex/detail/identifier_symbols.h
    lex/detail/symbol_range.h
    lex/detail/tokenize_keyword_or_identifier.h
    lex/detail/tokenize_number.h
    lex/detail/tokenize_string.h
    lex/detail/tokenizer.h
    lex/detail/tokenizer_state.h
    lex/attribute.h
    lex/error.h
    lex/keywords.h
    lex/symbol.h
    lex/token.h
    lex/token_list.h
    lex/token_source.h
    lex/tokenize.cpp
    lex/tokenize.h
    util/as_string.h
    util/box.h
    util/enum_class.h
    util/match.h
    util/named_tuple.h
    util/overloaded.h
    util/type_name.cpp
    util/type_name.h
    util/va_args.h
)

add_library(fp ${SOURCES})
target_use_packages(fp boost-preprocessor boost-range)
