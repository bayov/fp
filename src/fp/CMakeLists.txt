glob_sources(SOURCES *.h *.cpp)

add_library(fp ${SOURCES})
add_dependencies(fp ${SOURCES_DEP})
target_use_packages(fp boost-preprocessor)
