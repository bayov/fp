# Convinience wrapper over `ExternalProject_Add`.
#
# Use `package(...)` to add new packages, and apply them as dependencies using
# `target_use_package(...)`. Example:
#
#   include(package.cmake)
#
#   package(
#       gtest
#       GITHUB_REPO google/googletest
#       TAG release-1.8.0
#       SUBDIR googletest   # gtest's repo root CMakeLists.txt is under this dir
#       LIBRARIES gtest->pthread gtest_main->gtest
#       # Produces two library targets: `gtest` and `gtest_main`.
#       # To use `gtest`, we must link against `pthread` as well.
#       # To use `gtest_main`, we must link against the core `gtest`.
#   )
#
#   add_executable(my_test my_test.cpp)
#   target_use_package(my_test gtest LINK gtest_main)
#

include(CMakeParseArguments)
include(ExternalProject)

# default timeout for downloading packages
set(_PM_DEFAULT_TIMEOUT 10)

# root directory for pacakges
set(_PM_ROOT_DIR ${CMAKE_BINARY_DIR}/packages)

function(_set_default variable default)
    if(NOT ${variable})
        set(${variable} ${default} PARENT_SCOPE)
    endif()
endfunction()

# Throws a FATAL_ERROR for the given package `name`, with the given message
# string list, each in a line of its own.
function(_package_error name)
    string(REPLACE ";" "\n    " messages "${ARGN}")
    message(FATAL_ERROR "\n  Error in package(${name}):\n    ${messages}\n")
endfunction()

# Adds a library of a package:
#
#   - <library_dir>
#       The directory the library is installed in.
#
#   - <library_and_links>
#       The library's name, and optional transitive links to other libraries.
#       The format for links is:
#           target->link1,link2,link3
#       The library target is added using:
#           add_library(${target} STATIC IMPORTED)
#           set_target_properties(
#               ${target}
#               PROPERTIES IMPORTED_LOCATION ${library_dir}/lib${target}.a
#           )
#       The links are added using:
#           set_target_properties(
#               ${target}
#               PROPERTIES IMPORTED_LINK_INTERFACE_LIBRARIES "link1;link2;link3"
#           )
#
function(_package_add_library library_dir library_and_links)
    string(REPLACE "->" ";" lib_list ${library_and_links})
    list(GET lib_list 0 target)
    if(NOT target)
        _package_error(
            ${name}
            "LIBRARIES format is <library>-><link1>,<link2>,..."
            "E.g., mylib->mylib_core,some_other_lib"
            ""
            "Given ill-formatted library: ${library_and_links}"
        )
    endif()
    set(links ${lib_list})
    list(REMOVE_AT links 0)

    set(file lib${target}.a)
    add_library(${target} STATIC IMPORTED)
    set_target_properties(
        ${target} PROPERTIES IMPORTED_LOCATION ${library_dir}/${file}
    )
    if(links)
        string(REPLACE "," ";" links ${links})
        set_target_properties(
            ${target} PROPERTIES IMPORTED_LINK_INTERFACE_LIBRARIES "${links}"
        )
    endif()
endfunction()

# Create a minimal _CMakeLists.txt_ in the give <dir>, that simply installs the
# given <include_dir> DIRECTORY to CMAKE_INSTALL_PREFIX.
function(_create_cmakelists dir include_dir)
    set(f ${dir}/CMakeLists.txt)
    file(WRITE ${f})
    file(APPEND ${f} "cmake_minimum_required(VERSION ")
    file(APPEND ${f} "${CMAKE_MINIMUM_REQUIRED_VERSION})\n")
    file(APPEND ${f} "install(DIRECTORY ${include_dir} DESTINATION .)\n")
endfunction()

# Download and install an external package.
#
# This is a simple wrapper over `ExternalProject_Add`, a bit more user-friendly,
# with some additional features.
#
#   package(
#       <name>
#       GITHUB_REPO <github_repo>
#       [TAG <tag>]
#       [SUBDIR <subdir>
#       [INCLUDE_DIR <include_dir>]
#       [LIBRARY_DIR <library_dir>]
#       [CMAKE_ARGS <cmake_args> ...]
#       [LIBRARIES <libraries> ...]
#       [DEPENDENCIES <dependencies> ...]
#       [NO_CMAKE]
#   )
#
#   - <name>
#       The name of the package. The external-project target will be defined as
#       "${name}-package".
#
#   - <github_repo>
#       A GitHub repository to download from. Format is `<user>/<repo>`. The
#       actual download URL used is:
#           https://github.com/${github_repo}/archive/${tag}.zip
#
#   - <tag> (default "master")
#       A git tag for the given repository.
#
#   - <subdir> (default ".")
#       The relative path to the directory containing packages' CMakeLists.txt.
#
#   - <include_dir> (default "include")
#       The directory containing the package's headers (after installation).
#
#   - <library_dir> (default "lib")
#       The directory containing the package's libraries (after installation).
#
#   - <cmake_args>
#       Additional arguments to `cmake` for configuring the package build.
#
#   - <libraries>
#       Static libraries which the package provides. Each item in this list is
#       a library <target>:
#           add_library(${target} STATIC IMPORTED)
#           set_target_properties(
#               ${target}
#               PROPERTIES IMPORTED_LOCATION ${library_dir}/lib${target}.a
#           )
#       Additionally, each library target may specify one or more transitive
#       dependencies to other libraries using the following syntax:
#           target->link1,link2,link3
#       Which translates to:
#           set_target_properties(
#               ${target}
#               PROPERTIES IMPORTED_LINK_INTERFACE_LIBRARIES "link1;link2;link3"
#           )
#
#   - <dependencies>
#       Dependencies on other `package()`s.
#
#   - NO_CMAKE
#       For downloaded packages with no CMakeLists.txt. A custom CMakeLists.txt
#       will be created for the package after downloading and before building,
#       which contains a single instruction:
#           install(DIRECTORY ${include_dir} DESTINATION .)
#       Basically, installing the given <include_dir> to the install directory.
#
function(package name)
    set(flags NO_CMAKE)
    set(options GITHUB_REPO TAG SUBDIR INCLUDE_DIR LIBRARY_DIR)
    set(list_options CMAKE_ARGS LIBRARIES DEPENDENCIES)
    cmake_parse_arguments("" "${flags}" "${options}" "${list_options}" ${ARGN})
    _set_default(_TAG master)
    _set_default(_INCLUDE_DIR include)
    _set_default(_LIBRARY_DIR lib)

    if(_GITHUB_REPO)
        set(url https://github.com/${_GITHUB_REPO}/archive/${_TAG}.zip)
    else()
        _package_error(${name} "GITHUB_REPO must be given")
    endif()

    set(root_dir ${_PM_ROOT_DIR}/${name})
    set(install_dir ${root_dir}/install)
    set(subdir ${_SUBDIR})

    if(_NO_CMAKE)
        _create_cmakelists(${root_dir} src/${_INCLUDE_DIR})
        set(subdir ..)
    endif()

    ExternalProject_Add(
        ${name}-package
        URL ${url}
        TIMEOUT ${_PM_DEFAULT_TIMEOUT}
        UPDATE_COMMAND ""
        PREFIX ${root_dir}
        TMP_DIR ${root_dir}/tmp
        STAMP_DIR ${root_dir}/stamp
        SOURCE_DIR ${root_dir}/src
        SOURCE_SUBDIR ${subdir}
        BINARY_DIR ${root_dir}/build
        INSTALL_DIR ${install_dir}
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${install_dir} ${_CMAKE_ARGS}
    )
    include_directories(${install_dir}/${_INCLUDE_DIR})
    foreach(lib ${_LIBRARIES})
        _package_add_library(${install_dir}/${_LIBRARY_DIR} ${lib})
    endforeach()

    foreach(dependency ${_DEPENDENCIES})
        add_dependencies(${name}-package ${dependency}-package)
    endforeach()
endfunction()

# Add packages defined with `package()` as a dependencies of the given <target>.
#
#   target_use_packages(<target> <packages> ... [LINK <libraries> ...])
#
# LINK <libraries> are added simply by calling `target_link_libraries()`.
#
function(target_use_packages target)
    set(flags)
    set(options)
    set(list_options LINK)
    cmake_parse_arguments("" "${flags}" "${options}" "${list_options}" ${ARGN})
    foreach(package ${_UNPARSED_ARGUMENTS})
        add_dependencies(${target} ${package}-package)
    endforeach()
    if(_LINK)
        target_link_libraries(${target} ${_LINK})
    endif()
endfunction()