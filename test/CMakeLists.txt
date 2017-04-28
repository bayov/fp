package(
    gtest
    GITHUB_REPO google/googletest
    TAG release-1.8.0
    SUBDIR googletest
    LIBRARIES gtest->pthread gtest_main->gtest
)

include_directories(include)

glob_sources(SOURCES *.h *.cpp)

add_executable(fp_test ${SOURCES})
add_dependencies(fp_test ${SOURCES_DEP})
target_link_libraries(fp_test fp)
target_use_packages(fp_test gtest LINK gtest_main)
