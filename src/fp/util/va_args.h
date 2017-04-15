/**
 * This file provides definitions similar to Boost.Preprocessor's, but with
 * a limit of 256 elements instead of 64.
 *
 * This was generated with a one-time throw-away script, so hopefully we won't
 * ever need more than 256...
 */

#pragma once

#include <boost/preprocessor/cat.hpp>

/**
 * Expands to the number of given arguments.
 *
 * @example
 *
 *      VA_ARGS_SIZE(a, b, c) // expands to 3
 */
#define VA_ARGS_SIZE(...) VA_ARGS_SIZE_I(\
    __VA_ARGS__,\
    256, 255, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 243, 242,\
    241, 240, 239, 238, 237, 236, 235, 234, 233, 232, 231, 230, 229, 228, 227,\
    226, 225, 224, 223, 222, 221, 220, 219, 218, 217, 216, 215, 214, 213, 212,\
    211, 210, 209, 208, 207, 206, 205, 204, 203, 202, 201, 200, 199, 198, 197,\
    196, 195, 194, 193, 192, 191, 190, 189, 188, 187, 186, 185, 184, 183, 182,\
    181, 180, 179, 178, 177, 176, 175, 174, 173, 172, 171, 170, 169, 168, 167,\
    166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 156, 155, 154, 153, 152,\
    151, 150, 149, 148, 147, 146, 145, 144, 143, 142, 141, 140, 139, 138, 137,\
    136, 135, 134, 133, 132, 131, 130, 129, 128, 127, 126, 125, 124, 123, 122,\
    121, 120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107,\
    106, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90,\
    89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71,\
    70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52,\
    51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33,\
    32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14,\
    13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1\
)

#define VA_ARGS_SIZE_I(\
    a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17,\
    a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, a32,\
    a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, a47,\
    a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, a62,\
    a63, a64, a65, a66, a67, a68, a69, a70, a71, a72, a73, a74, a75, a76, a77,\
    a78, a79, a80, a81, a82, a83, a84, a85, a86, a87, a88, a89, a90, a91, a92,\
    a93, a94, a95, a96, a97, a98, a99, a100, a101, a102, a103, a104, a105,\
    a106, a107, a108, a109, a110, a111, a112, a113, a114, a115, a116, a117,\
    a118, a119, a120, a121, a122, a123, a124, a125, a126, a127, a128, a129,\
    a130, a131, a132, a133, a134, a135, a136, a137, a138, a139, a140, a141,\
    a142, a143, a144, a145, a146, a147, a148, a149, a150, a151, a152, a153,\
    a154, a155, a156, a157, a158, a159, a160, a161, a162, a163, a164, a165,\
    a166, a167, a168, a169, a170, a171, a172, a173, a174, a175, a176, a177,\
    a178, a179, a180, a181, a182, a183, a184, a185, a186, a187, a188, a189,\
    a190, a191, a192, a193, a194, a195, a196, a197, a198, a199, a200, a201,\
    a202, a203, a204, a205, a206, a207, a208, a209, a210, a211, a212, a213,\
    a214, a215, a216, a217, a218, a219, a220, a221, a222, a223, a224, a225,\
    a226, a227, a228, a229, a230, a231, a232, a233, a234, a235, a236, a237,\
    a238, a239, a240, a241, a242, a243, a244, a245, a246, a247, a248, a249,\
    a250, a251, a252, a253, a254, a255, a256, size, ...\
) size

/**
 * Expands the given arguments to a Boost.Preprocessor sequence.
 *
 * @example
 *
 *      VA_ARGS_TO_SEQ(a, b, c) // expands to (a)(b)(c)
 */
#define VA_ARGS_TO_SEQ(...) VA_ARGS_TUPLE_TO_SEQ((__VA_ARGS__))

/**
 * Expands the given Boost.Preprocessor tuple to a sequence.
 *
 * @example
 *
 *      VA_ARGS_TUPLE_TO_SEQ((a, b, c)) // expands to (a)(b)(c)
 */
#define VA_ARGS_TUPLE_TO_SEQ(va_args)\
    BOOST_PP_CAT(VA_ARGS_TUPLE_TO_SEQ_, VA_ARGS_SIZE va_args) va_args

/*
 * This monstrosity is basically expanding the tuple recursively, 32 arguments
 * at a time. Why not just use a recursion for every argument? Performance :(
 */
#define VA_ARGS_TUPLE_TO_SEQ_1(a1) (a1)
#define VA_ARGS_TUPLE_TO_SEQ_2(a1, a2) (a1)(a2)
#define VA_ARGS_TUPLE_TO_SEQ_3(a1, a2, a3) (a1)(a2)(a3)
#define VA_ARGS_TUPLE_TO_SEQ_4(a1, a2, a3, a4) (a1)(a2)(a3)(a4)
#define VA_ARGS_TUPLE_TO_SEQ_5(a1, a2, a3, a4, a5) (a1)(a2)(a3)(a4)(a5)
#define VA_ARGS_TUPLE_TO_SEQ_6(a1, a2, a3, a4, a5, a6) (a1)(a2)(a3)(a4)(a5)(a6)
#define VA_ARGS_TUPLE_TO_SEQ_7(a1, a2, a3, a4, a5, a6, a7) (a1)(a2)(a3)(a4)(a5)(a6)(a7)
#define VA_ARGS_TUPLE_TO_SEQ_8(a1, a2, a3, a4, a5, a6, a7, a8) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)
#define VA_ARGS_TUPLE_TO_SEQ_9(a1, a2, a3, a4, a5, a6, a7, a8, a9) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)
#define VA_ARGS_TUPLE_TO_SEQ_10(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)
#define VA_ARGS_TUPLE_TO_SEQ_11(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)
#define VA_ARGS_TUPLE_TO_SEQ_12(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)
#define VA_ARGS_TUPLE_TO_SEQ_13(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)
#define VA_ARGS_TUPLE_TO_SEQ_14(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)
#define VA_ARGS_TUPLE_TO_SEQ_15(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)
#define VA_ARGS_TUPLE_TO_SEQ_16(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)
#define VA_ARGS_TUPLE_TO_SEQ_17(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)
#define VA_ARGS_TUPLE_TO_SEQ_18(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)
#define VA_ARGS_TUPLE_TO_SEQ_19(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)
#define VA_ARGS_TUPLE_TO_SEQ_20(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)
#define VA_ARGS_TUPLE_TO_SEQ_21(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)
#define VA_ARGS_TUPLE_TO_SEQ_22(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)
#define VA_ARGS_TUPLE_TO_SEQ_23(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)
#define VA_ARGS_TUPLE_TO_SEQ_24(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)
#define VA_ARGS_TUPLE_TO_SEQ_25(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)
#define VA_ARGS_TUPLE_TO_SEQ_26(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)
#define VA_ARGS_TUPLE_TO_SEQ_27(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)
#define VA_ARGS_TUPLE_TO_SEQ_28(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)
#define VA_ARGS_TUPLE_TO_SEQ_29(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)
#define VA_ARGS_TUPLE_TO_SEQ_30(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)(a30)
#define VA_ARGS_TUPLE_TO_SEQ_31(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)(a30)(a31)
#define VA_ARGS_TUPLE_TO_SEQ_32(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, a32) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)(a30)(a31)(a32)
#define VA_ARGS_TUPLE_TO_SEQ_33(a1, ...) (a1)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_34(a1, a2, ...) (a1)(a2)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_35(a1, a2, a3, ...) (a1)(a2)(a3)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_36(a1, a2, a3, a4, ...) (a1)(a2)(a3)(a4)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_37(a1, a2, a3, a4, a5, ...) (a1)(a2)(a3)(a4)(a5)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_38(a1, a2, a3, a4, a5, a6, ...) (a1)(a2)(a3)(a4)(a5)(a6)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_39(a1, a2, a3, a4, a5, a6, a7, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_40(a1, a2, a3, a4, a5, a6, a7, a8, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_41(a1, a2, a3, a4, a5, a6, a7, a8, a9, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_42(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_43(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_44(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_45(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_46(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_47(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_48(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_49(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_50(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_51(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_52(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_53(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_54(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_55(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_56(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_57(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_58(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_59(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_60(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_61(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_62(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)(a30)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_63(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)(a30)(a31)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_64(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, a32, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)(a30)(a31)(a32)VA_ARGS_TUPLE_TO_SEQ_32(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_65(a1, ...) (a1)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_66(a1, a2, ...) (a1)(a2)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_67(a1, a2, a3, ...) (a1)(a2)(a3)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_68(a1, a2, a3, a4, ...) (a1)(a2)(a3)(a4)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_69(a1, a2, a3, a4, a5, ...) (a1)(a2)(a3)(a4)(a5)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_70(a1, a2, a3, a4, a5, a6, ...) (a1)(a2)(a3)(a4)(a5)(a6)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_71(a1, a2, a3, a4, a5, a6, a7, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_72(a1, a2, a3, a4, a5, a6, a7, a8, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_73(a1, a2, a3, a4, a5, a6, a7, a8, a9, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_74(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_75(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_76(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_77(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_78(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_79(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_80(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_81(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_82(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_83(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_84(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_85(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_86(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_87(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_88(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_89(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_90(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_91(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_92(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_93(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_94(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)(a30)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_95(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)(a30)(a31)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_96(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, a32, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)(a30)(a31)(a32)VA_ARGS_TUPLE_TO_SEQ_64(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_97(a1, ...) (a1)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_98(a1, a2, ...) (a1)(a2)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_99(a1, a2, a3, ...) (a1)(a2)(a3)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_100(a1, a2, a3, a4, ...) (a1)(a2)(a3)(a4)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_101(a1, a2, a3, a4, a5, ...) (a1)(a2)(a3)(a4)(a5)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_102(a1, a2, a3, a4, a5, a6, ...) (a1)(a2)(a3)(a4)(a5)(a6)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_103(a1, a2, a3, a4, a5, a6, a7, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_104(a1, a2, a3, a4, a5, a6, a7, a8, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_105(a1, a2, a3, a4, a5, a6, a7, a8, a9, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_106(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_107(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_108(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_109(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_110(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_111(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_112(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_113(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_114(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_115(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_116(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_117(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_118(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_119(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_120(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_121(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_122(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_123(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_124(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_125(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_126(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)(a30)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_127(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)(a30)(a31)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_128(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, a32, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)(a30)(a31)(a32)VA_ARGS_TUPLE_TO_SEQ_96(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_129(a1, ...) (a1)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_130(a1, a2, ...) (a1)(a2)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_131(a1, a2, a3, ...) (a1)(a2)(a3)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_132(a1, a2, a3, a4, ...) (a1)(a2)(a3)(a4)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_133(a1, a2, a3, a4, a5, ...) (a1)(a2)(a3)(a4)(a5)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_134(a1, a2, a3, a4, a5, a6, ...) (a1)(a2)(a3)(a4)(a5)(a6)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_135(a1, a2, a3, a4, a5, a6, a7, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_136(a1, a2, a3, a4, a5, a6, a7, a8, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_137(a1, a2, a3, a4, a5, a6, a7, a8, a9, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_138(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_139(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_140(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_141(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_142(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_143(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_144(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_145(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_146(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_147(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_148(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_149(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_150(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_151(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_152(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_153(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_154(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_155(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_156(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_157(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_158(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)(a30)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_159(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)(a30)(a31)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_160(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, a32, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)(a30)(a31)(a32)VA_ARGS_TUPLE_TO_SEQ_128(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_161(a1, ...) (a1)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_162(a1, a2, ...) (a1)(a2)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_163(a1, a2, a3, ...) (a1)(a2)(a3)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_164(a1, a2, a3, a4, ...) (a1)(a2)(a3)(a4)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_165(a1, a2, a3, a4, a5, ...) (a1)(a2)(a3)(a4)(a5)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_166(a1, a2, a3, a4, a5, a6, ...) (a1)(a2)(a3)(a4)(a5)(a6)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_167(a1, a2, a3, a4, a5, a6, a7, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_168(a1, a2, a3, a4, a5, a6, a7, a8, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_169(a1, a2, a3, a4, a5, a6, a7, a8, a9, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_170(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_171(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_172(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_173(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_174(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_175(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_176(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_177(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_178(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_179(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_180(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_181(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_182(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_183(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_184(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_185(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_186(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_187(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_188(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_189(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_190(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)(a30)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_191(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)(a30)(a31)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_192(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, a32, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)(a30)(a31)(a32)VA_ARGS_TUPLE_TO_SEQ_160(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_193(a1, ...) (a1)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_194(a1, a2, ...) (a1)(a2)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_195(a1, a2, a3, ...) (a1)(a2)(a3)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_196(a1, a2, a3, a4, ...) (a1)(a2)(a3)(a4)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_197(a1, a2, a3, a4, a5, ...) (a1)(a2)(a3)(a4)(a5)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_198(a1, a2, a3, a4, a5, a6, ...) (a1)(a2)(a3)(a4)(a5)(a6)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_199(a1, a2, a3, a4, a5, a6, a7, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_200(a1, a2, a3, a4, a5, a6, a7, a8, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_201(a1, a2, a3, a4, a5, a6, a7, a8, a9, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_202(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_203(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_204(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_205(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_206(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_207(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_208(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_209(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_210(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_211(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_212(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_213(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_214(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_215(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_216(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_217(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_218(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_219(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_220(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_221(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_222(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)(a30)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_223(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)(a30)(a31)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_224(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, a32, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)(a30)(a31)(a32)VA_ARGS_TUPLE_TO_SEQ_192(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_225(a1, ...) (a1)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_226(a1, a2, ...) (a1)(a2)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_227(a1, a2, a3, ...) (a1)(a2)(a3)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_228(a1, a2, a3, a4, ...) (a1)(a2)(a3)(a4)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_229(a1, a2, a3, a4, a5, ...) (a1)(a2)(a3)(a4)(a5)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_230(a1, a2, a3, a4, a5, a6, ...) (a1)(a2)(a3)(a4)(a5)(a6)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_231(a1, a2, a3, a4, a5, a6, a7, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_232(a1, a2, a3, a4, a5, a6, a7, a8, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_233(a1, a2, a3, a4, a5, a6, a7, a8, a9, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_234(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_235(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_236(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_237(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_238(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_239(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_240(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_241(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_242(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_243(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_244(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_245(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_246(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_247(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_248(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_249(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_250(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_251(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_252(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_253(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_254(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)(a30)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_255(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)(a30)(a31)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
#define VA_ARGS_TUPLE_TO_SEQ_256(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, a32, ...) (a1)(a2)(a3)(a4)(a5)(a6)(a7)(a8)(a9)(a10)(a11)(a12)(a13)(a14)(a15)(a16)(a17)(a18)(a19)(a20)(a21)(a22)(a23)(a24)(a25)(a26)(a27)(a28)(a29)(a30)(a31)(a32)VA_ARGS_TUPLE_TO_SEQ_224(__VA_ARGS__)
