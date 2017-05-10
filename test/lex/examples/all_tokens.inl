constexpr auto in = R"fp(

    "string" , : ;
    ? @ ~ . .. ...

    # brackets
    ( ) [ ] { }

    # (some) keywords
    if and or not

    # arrows
    -> =>

    # arithmetic
    + - * / % ** & | ^ << >>

    # assignments
    = += -= *= /= %= **=
    &= |= ^= <<= >>=

    # comparisons
    == != < > <= >=

    # increment & decrement
    ++ --

    # containing attributes
    an_identifier 42 3.14 'a'

)fp";

constexpr auto expected = R"tokens(

    QUOTE STRING(string) QUOTE COMMA ANNOTATION SEMICOLON
    OPTIONAL DECORATOR BIT_NOT MEMBER_ACCESS RANGE CLOSED_RANGE

    COMMENT(# brackets)
    L_PAREN R_PAREN L_BRACKET R_BRACKET L_BRACE R_BRACE

    COMMENT(# (some) keywords)
    IF AND OR NOT

    COMMENT(# arrows)
    TYPE_ARROW LAMBDA_ARROW

    COMMENT(# arithmetic)
    PLUS MINUS MUL DIV MOD POW BIT_AND BIT_OR XOR LSHIFT RSHIFT

    COMMENT(# assignments)
    ASSIGN PLUS_ASSIGN MINUS_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN POW_ASSIGN
    BIT_AND_ASSIGN BIT_OR_ASSIGN XOR_ASSIGN LSHIFT_ASSIGN RSHIFT_ASSIGN

    COMMENT(# comparisons)
    EQ NE LT GT LTE GTE

    COMMENT(# increment & decrement)
    INC DEC

    COMMENT(# containing attributes)
    IDENTIFIER(an_identifier) INTEGER(42) FLOAT(3.14) CHAR(97)

)tokens";
