include(FetchContent)

# Tags: https://github.com/doctest/doctest/tags
set(NEEDED_DOCTEST_VERSION "2.4.10")

find_package(doctest ${NEEDED_DOCTEST_VERSION} QUIET)

if (NOT doctest_FOUND)

    FetchContent_Declare(
        doctest
        GIT_REPOSITORY "https://github.com/doctest/doctest"
        GIT_TAG        v${NEEDED_DOCTEST_VERSION}
        GIT_SHALLOW    TRUE
    )

    FetchContent_MakeAvailable(doctest)

    # include the doctest module that contains doctest_discover_tests
    list(APPEND CMAKE_MODULE_PATH ${doctest_SOURCE_DIR}/scripts/cmake)

endif()

# this needs to be called for the doctest_discover_tests function to work
include(doctest)

add_executable(testrunner

    main.cpp

    lottery/combination_table_tests.cpp
    lottery/combination_value_tests.cpp
    lottery/lottery_odds_tests.cpp
    lottery/ranking_combinations_tests.cpp
    lottery/ranking_tests.cpp

    math/cmath_tests.cpp

    team_tests.cpp
    text_literals_tests.cpp

)

target_link_libraries(testrunner
    PRIVATE
        doctest::doctest
        nhl::nhl
)

doctest_discover_tests(testrunner)
