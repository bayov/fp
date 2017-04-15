# Builds upon `package.cmake` to define simple wrappers for Boost components:
#
#   boost_package(optional DEPENDENCIES core assert type_traits ...)
#   boost_package(variant DEPENDENCIES ...)
#   finalize_boost_packages(boost-1.63.0)
#
# This translate to calls of the form:
#
#   package(
#       boost-optional
#       GITHUB_REPO boostorg/optional
#       TAG boost-1.63.0
#       DEPENDENCIES boost-core boost-assert boost-type_traits ...
#       NO_CMAKE
#   )
#
# Additionally, for each component in DEPENDENCIES, a new `package()` is created
# if none exists. The functions maintain a dependency tree to ensure correct
# creation of the packages.
#

include(cmake/package.cmake)

# Stores a dependency tree of Boost components as specified by multiple calls to
# `boost_package(...)`. The tree is stored as a ;-list of items formatted as:
#
#       #begin;c1;#dep:d1,#dep:d2;c2;#none;c3;#dep:d3
#
# Basically, a component followed by a comma-separated list of its dependencies.
#
set(ENV{_PM_BOOST_PACKAGES} "#begin")

# Define a Boost component package:
#
#   boost_package(<component> [DEPENDENCIES <dependencies> ...])
#
# Will be translated to:
#
#   package(
#       boost-${component}
#       GITHUB_REPO boostorg/${component}
#       TAG ${tag}
#       DEPENDENCIES ${dependencies}
#       NO_CMAKE
#   )
#
# Every specified dependency will also be translated to a similar `package()`
# call.
#
# These packages will be defined only after calling `finalize_boost_packages()`.
#
function(boost_package component)
    set(flags)
    set(options)
    set(list_options DEPENDENCIES)
    cmake_parse_arguments("" "${flags}" "${options}" "${list_options}" ${ARGN})

    if(_DEPENDENCIES)
        string(REPLACE ";" ",#dep:" deps "#dep:${_DEPENDENCIES}")
    else()
        set(deps "#none")
    endif()
    set(
        ENV{_PM_BOOST_PACKAGES}
        "$ENV{_PM_BOOST_PACKAGES};boost-${component};${deps}"
    )
endfunction()

# Define a Boost package for the given component, if no such target exists.
function(_define_boost_package component dependencies tag)
    string(REPLACE "boost-" "" component ${component})
    if(TARGET boost-${component}-package)
        return()
    endif()
    package(
        boost-${component}
        GITHUB_REPO boostorg/${component}
        TAG ${tag}
        DEPENDENCIES ${dependencies}
        NO_CMAKE
    )
endfunction()

# Pop the Boost component at index <i> of the `ENV{_PM_BOOST_PACKAGES}`
# dependency tree, and defines boost packages for the package and all of its
# dependencies transitivly (which will be popped recursively).
function(_pop_boost_package i tag)
    STRING(REPLACE "#begin;" "" packages "$ENV{_PM_BOOST_PACKAGES}")
    if(NOT packages)
        return()
    endif()

    math(EXPR di "${i} + 1")
    list(GET packages ${i} component)
    list(GET packages ${di} deps)
    list(REMOVE_AT packages ${i} ${di})
    set(ENV{_PM_BOOST_PACKAGES} "#begin;${packages}")

    if(deps STREQUAL "#none")
        set(deps "")
    else()
        string(REPLACE "," ";" deps "${deps}")
        string(REPLACE "#dep:" "boost-" deps "${deps}")
    endif()

    foreach(dep ${deps})
        list(FIND packages ${dep} dep_index)
        if(dep_index EQUAL -1)
            _define_boost_package(${dep} "" ${tag})
            continue()
        endif()
        _pop_boost_package(${dep_index} ${tag})
    endforeach()
    _define_boost_package(${component} "${deps}" ${tag})
endfunction()

# Finalize all calls to `boost_package(...)`, which actually defines the
# packages. The given <tag> will be the Git repository tag to build the Boost
# components from.
function(finalize_boost_packages tag)
    while(1)
        STRING(REPLACE "#begin;" "" packages $ENV{_PM_BOOST_PACKAGES})
        if(packages STREQUAL "#begin")
            break()
        endif()
        _pop_boost_package(0 ${tag})
    endwhile()
endfunction()
