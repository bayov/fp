constexpr auto in = R"fp(

    "42 is {42}."

    "multi depth interpolation {
        "depth 1 {
            "depth 2 {blah}"
        }"
    }"

    "brace balancing {
        { 1 { 2 {} } }
    }"

    "multi brace balancing {
        { { "depth 1 {
            { "depth 2 { }" }
        }" } }
    }"

)fp";

constexpr auto expected = R"tokens(

    QUOTE STRING(42 is ) L_BRACE INTEGER(42) R_BRACE STRING(.) QUOTE

    QUOTE STRING(multi depth interpolation ) L_BRACE
        QUOTE STRING(depth 1 ) L_BRACE
            QUOTE STRING(depth 2 ) L_BRACE IDENTIFIER(blah) R_BRACE QUOTE
        R_BRACE QUOTE
    R_BRACE QUOTE

    QUOTE STRING(brace balancing ) L_BRACE
        L_BRACE INTEGER(1) L_BRACE INTEGER(2) L_BRACE R_BRACE R_BRACE R_BRACE
    R_BRACE QUOTE

    QUOTE STRING(multi brace balancing ) L_BRACE
        L_BRACE L_BRACE QUOTE STRING(depth 1 ) L_BRACE
            L_BRACE QUOTE STRING(depth 2 ) L_BRACE R_BRACE QUOTE R_BRACE
        R_BRACE QUOTE R_BRACE R_BRACE
    R_BRACE QUOTE

)tokens";
