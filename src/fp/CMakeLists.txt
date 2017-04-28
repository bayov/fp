glob_sources(SOURCES *.h *.cpp)

add_library(fp ${SOURCES})
target_use_packages(fp boost-preprocessor boost-range)
