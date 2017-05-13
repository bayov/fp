import common::types::input;
import common::types::integer_t;
import keywords;

export as variant {
    QUOTE,          # "
    COMMA,          # ,
    ANNOTATION,     # :
    # ...

    # keywords
    ...(keyword.uppercase() for keyword in keywords),

    COMMENT(input::view),
    INTEGER(integer_t),
    STRING(string),
    # ...
};
