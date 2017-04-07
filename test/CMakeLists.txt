include(ExternalProject)

ExternalProject_Add(
    fiddle
    GIT_REPOSITORY https://github.com/sosz/temp-cpp.git
    PREFIX fiddle
    INSTALL_DIR install
)
