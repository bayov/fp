#pragma once

#include <type_traits>
#include <string>

#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/transform.hpp>

#include "va_args.h"

namespace fp::util {

/**
 * Define an `enum class` with additional reflective utilities (for both
 * run-time and compile-time information).
 *
 * The `enum class` definition is:
 *
 *      enum class name : type { enumerators };
 *
 * @example
 *
 *      ENUM_CLASS(suit, uint8_t, DIAMONDS, CLUBS, HEARTS, SPADES);
 *
 *      util::enum_class<suit>::name; // "suit"
 *      util::enum_class<suit>::size; // 4
 *
 *      // compile-time traits are under:
 *      util::enum_class<suit>::enumerator_traits<suit::CLUBS>::name; // "CLUBS"
 *
 *      // but it is easier to access using this macro:
 *      ENUMERATOR(suit::CLUBS)::name; // "CLUBS"
 *
 *      // run-time traits are under:
 *      util::enum_class<suit>::enumerator_info(suit::CLUBS).name(); // "CLUBS"
 *
 *      // but it is easier to access using this function:
 *      util::enumerator(suit::CLUBS).name(); // "CLUBS"
 *
 */
#define ENUM_CLASS(name, type, enumerators...)\
    ENUM_CLASS_I(name, type, VA_ARGS_TO_SEQ(enumerators), enumerators)

#define ENUM_CLASS_I(name, type, enumerators, ...)\
    enum class name : type { __VA_ARGS__ };\
    ENUM_CLASS_TRAITS(name, type, enumerators)

/// A compile-time list of enumerators.
template <class Enum, Enum... ENUMERATORS>
struct enumerator_sequence {
    using enum_type = Enum;
    static constexpr size_t size = sizeof...(ENUMERATORS);
};

namespace detail {

/**
 * Uses ADL to find a traits class for the given enum. This is a small hack to
 * bypass the limitation that we can't specialize util::enum_class inside
 * unrelated namespaces.
 */
template <class Enum>
using enum_class_traits =
    std::remove_cv_t<decltype(get_enum_class_traits_of(Enum{}))>;

#define ENUM_CLASS_ENUMERATOR_STRING(_1, _2, enumerator) #enumerator

#define ENUM_CLASS_ENUMERATOR_QUALIFIED(_1, name, enumerator) name::enumerator

#define ENUM_CLASS_TRAITS(enum_name, type, enumerators)\
    struct enum_class_##enum_name##_traits {\
        static constexpr auto name = #enum_name;\
        using underlying_type = type;\
        static constexpr const char* enumerator_names[] = {\
            BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TRANSFORM_S(\
                1, ENUM_CLASS_ENUMERATOR_STRING, _, enumerators\
            ))\
        };\
        using sequence = fp::util::enumerator_sequence<\
            enum_name,\
            BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TRANSFORM_S(\
                1, ENUM_CLASS_ENUMERATOR_QUALIFIED, enum_name, enumerators\
            ))\
        >;\
        static constexpr size_t size = sequence::size;\
    };\
    enum_class_##enum_name##_traits get_enum_class_traits_of(enum_name)

} // detail

/// Utilities for `enum class`es defined using ENUM_CLASS.
template <class Enum>
class enum_class {

    using traits = detail::enum_class_traits<Enum>;

public:

    static constexpr const char* name = traits::name;
    using enum_type = Enum;
    using underlying_type = typename traits::underlying_type;
    static constexpr size_t size = traits::size;

    /// An compile-time list of all enumerators in the enum class.
    using sequence = typename traits::sequence;

    /// Compile-time traits for enumerators.
    template <Enum ENUMERATOR>
    struct enumerator_traits {
        static constexpr size_t index = size_t(ENUMERATOR);
        static constexpr const char* name = traits::enumerator_names[index];
    };

    /// Run-time traits for enumerators.
    class enumerator_info {
    public:

        constexpr enumerator_info(Enum enumerator) noexcept :
            m_enumerator(enumerator) {}

        constexpr size_t index() const noexcept { return size_t(m_enumerator); }
        std::string name() const { return traits::enumerator_names[index()]; }
        constexpr Enum value() const noexcept { return m_enumerator; }

    private:

        Enum m_enumerator;

    };

};

/// Access compile-time traits of enumerator defined with ENUM_CLASS.
#define ENUMERATOR(enumerator)\
    fp::util::enum_class<decltype(enumerator)>::enumerator_traits<enumerator>

/// Access run-time traits of enumerator defined with ENUM_CLASS.
template <class Enum>
typename enum_class<Enum>::enumerator_info enumerator(Enum enumerator) {
    return typename enum_class<Enum>::enumerator_info(enumerator);
}

} // fp::util
