cmake_minimum_required(VERSION 3.26.0)

project(nhl
    VERSION 0.1.0
    LANGUAGES CXX
)

# Tags: https://github.com/fmtlib/fmt/tags
# Linkage: target_link_libraries(fmt::fmt)
set(NEEDED_fmt_VERSION "9.1.0")

find_package(fmt ${NEEDED_fmt_VERSION} QUIET)

if (NOT fmt_FOUND)

    FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG        ${NEEDED_fmt_VERSION}
        GIT_SHALLOW    TRUE
    )

    FetchContent_MakeAvailable(fmt)

endif()

add_subdirectory(include)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)

    option(NHL_BUILD_TESTS "Enable or disable the building of tests" ON)
    option(NHL_BUILD_EXAMPLES "Enable or disable the building of examples" ON)
    option(NHL_BUILD_BENCHMARKS "Enable or disable the building of benchmarks" ON)
    option(NHL_ENABLE_INSTALL "Enable or disable the install rule" ON)

    if (NHL_BUILD_TESTS)
        enable_testing()
        add_subdirectory(tests)
    endif()

    if (NHL_BUILD_EXAMPLES)
        add_subdirectory(examples)
    endif()

    if (NHL_BUILD_BENCHMARKS)
        add_subdirectory(benchmarks)
    endif()

    if (NHL_ENABLE_INSTALL)

        include(GNUInstallDirs)
        include(CMakePackageConfigHelpers)

        # NOTE 1: The XXX_PACKAGE_TARGETS variable is referenced inside of the
        # xxxConfig.cmake.in file, so if the name of this variable changes, it
        # must be updated inside of the xxxConfig.cmake.in file.
        #
        # NOTE 2: If value of this variable changes, the xxxConfig.cmake.in file
        # name must be renamed to match the new value.
        set(NHL_PACKAGE_NAME ${PROJECT_NAME})
        set(NHL_PACKAGE_TARGETS ${NHL_PACKAGE_NAME}Targets)

        set(NHL_INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR})
        set(NHL_INSTALL_CMAKE_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/${NHL_PACKAGE_NAME})

        set(NHL_CONFIG_DIR ${PROJECT_BINARY_DIR}/cmake)
        set(NHL_CONFIG_IN cmake/${NHL_PACKAGE_NAME}Config.cmake.in)
        set(NHL_CONFIG ${NHL_CONFIG_DIR}/${NHL_PACKAGE_NAME}Config.cmake)
        set(NHL_CONFIG_VERSION ${NHL_CONFIG_DIR}/${NHL_PACKAGE_NAME}ConfigVersion.cmake)

        configure_package_config_file(
            ${NHL_CONFIG_IN}
            ${NHL_CONFIG}
            INSTALL_DESTINATION ${NHL_INSTALL_CMAKE_DIR}
        )

        # major.minor.patch1 is compatible with major.minor.patch2..n
        # if no VERSION is specified, the ${PROJECT_VERSION} variable will be
        # used. if the ${PROJECT_VERSION} is not set, CMake will output an
        # error
        write_basic_package_version_file(
            ${NHL_CONFIG_VERSION}
            COMPATIBILITY SameMinorVersion
        )

        install(
            FILES
                ${NHL_CONFIG}
                ${NHL_CONFIG_VERSION}
            DESTINATION ${NHL_INSTALL_CMAKE_DIR}
        )

        install(TARGETS ${NHL_PACKAGE_NAME}
            EXPORT ${NHL_PACKAGE_TARGETS}
            FILE_SET HEADERS
        )

        install(EXPORT ${NHL_PACKAGE_TARGETS}
            NAMESPACE ${NHL_PACKAGE_NAME}::
            DESTINATION ${NHL_INSTALL_CMAKE_DIR}
        )

    endif()

endif()
