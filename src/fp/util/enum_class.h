#pragma once

#include <type_traits>
#include <string>

#include <boost/preprocessor/stringize.hpp>

#include <fp/util/va_args.h>
#include <fp/util/pp_seq.h>

namespace fp::util {

/**
 * Define an `enum class` with additional reflective utilities (with both
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
 *      // but it is easier to access using this typedef:
 *      enumerator<suit::CLUBS>::name; // "CLUBS"
 *
 *      // run-time traits are under:
 *      util::enum_class<suit>::enumerator_info(suit::CLUBS).name(); // "CLUBS"
 *
 *      // but it is easier to access using this function:
 *      util::info(suit::CLUBS).name(); // "CLUBS"
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

#define ENUM_CLASS_ENUMERATOR_QUALIFIED(enumerator) enum_type::enumerator

#define ENUM_CLASS_TRAITS(enum_name, type, enumerators)\
    struct enum_class_##enum_name##_traits {\
        using enum_type = enum_name;\
        static constexpr auto name = #enum_name;\
        using underlying_type = type;\
        static constexpr const char* enumerator_names[] = {\
            SEQ_ENUM(enumerators, BOOST_PP_STRINGIZE)\
        };\
        using sequence = ::fp::util::enumerator_sequence<\
            enum_name,\
            SEQ_ENUM(enumerators, ENUM_CLASS_ENUMERATOR_QUALIFIED)\
        >;\
        static constexpr size_t size = sequence::size;\
    };\
    enum_class_##enum_name##_traits get_enum_class_traits_of(enum_name)

} // namespace detail

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

/// Access compile-time traits of an enumerator defined with ENUM_CLASS.
template <auto ENUMERATOR>
using enumerator =
    typename enum_class<decltype(ENUMERATOR)>::template enumerator_traits<ENUMERATOR>;

/// Access run-time traits of an enumerator defined with ENUM_CLASS.
template <class Enum>
typename enum_class<Enum>::enumerator_info info(Enum enumerator) {
    return typename enum_class<Enum>::enumerator_info(enumerator);
}

} // namespace fp::util
