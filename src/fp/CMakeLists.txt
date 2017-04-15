set(
    SOURCES
    lex/attribute.h
    lex/error.h
    lex/symbol.h
    lex/token.h
    lex/token_list.h
    lex/token_source.h
    lex/tokenize.cpp
    lex/tokenize.h
    util/as_string.h
    util/enum_class.h
    util/fundamental.h
    util/named_tuple.h
    util/type_name.cpp
    util/type_name.h
    util/va_args.h
)

add_library(fp ${SOURCES})
target_use_packages(fp boost-preprocessor boost-range)
