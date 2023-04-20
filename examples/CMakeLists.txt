# Tags: https://github.com/p-ranav/cxxopts/tags
# Linkage: target_link_libraries(cxxopts::cxxopts)
set(NEEDED_cxxopts_VERSION "3.1.1")

find_package(cxxopts ${NEEDED_cxxopts_VERSION} QUIET)

if (NOT cxxopts_FOUND)

    FetchContent_Declare(
        cxxopts
        GIT_REPOSITORY http://github.com/jarro2783/cxxopts
        GIT_TAG        v${NEEDED_cxxopts_VERSION}
        GIT_SHALLOW    TRUE
    )

    FetchContent_MakeAvailable(cxxopts)

endif()

add_executable(nhl_dls

    main.cpp

)

target_link_libraries(nhl_dls PRIVATE nhl::nhl cxxopts::cxxopts)
