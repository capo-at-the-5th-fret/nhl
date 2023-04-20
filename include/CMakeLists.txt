include(FetchContent)

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

add_library(nhl INTERFACE)
add_library(nhl::nhl ALIAS nhl)

target_sources(nhl
    INTERFACE
        FILE_SET HEADERS
        FILES
            nhl/conference.h
            nhl/division.h
            nhl/game.h
            nhl/league.h
            nhl/lottery.h
            nhl/schedule.h
            nhl/standings.h
            nhl/team_record.h
            nhl/team.h
            nhl/text_literals.h

            nhl/lottery/ball.h
            nhl/lottery/combination.h
            nhl/lottery/combination_table.h
            nhl/lottery/combination_value.h
            nhl/lottery/lottery.h
            nhl/lottery/machine.h
            nhl/lottery/odds.h
            nhl/lottery/print.h
            nhl/lottery/ranking.h
            nhl/lottery/ranking_combinations.h
            nhl/lottery/stats.h
            nhl/lottery/team.h
            nhl/lottery/teams.h
)

target_compile_features(nhl INTERFACE cxx_std_23)
target_link_libraries(nhl INTERFACE fmt::fmt)