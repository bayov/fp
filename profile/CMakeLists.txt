glob_sources(SOURCES *.h *.cpp)

add_executable(fp_profile EXCLUDE_FROM_ALL ${SOURCES})
add_dependencies(fp_profile ${SOURCES_DEP})
target_link_libraries(fp_profile fp profiler)
