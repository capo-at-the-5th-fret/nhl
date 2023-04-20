#pragma once

#include <string_view>
#include <array>
#include <algorithm>

namespace nhl::text_literals
{
    using namespace std::string_view_literals;

    inline constexpr std::string_view unknown{ "?" };

    inline constexpr std::array conference_ids =
    {
        "east"sv,
        "west"sv
    };
    static_assert(conference_ids.size() == 2);
    static_assert(std::ranges::is_sorted(conference_ids));
    static_assert(std::ranges::adjacent_find(conference_ids) ==
        std::ranges::end(conference_ids));

    inline constexpr std::array conference_names =
    {
        "Eastern"sv,
        "Western"sv
    };
    static_assert(conference_ids.size() == 2);
    static_assert(std::ranges::is_sorted(conference_names));
    static_assert(std::ranges::adjacent_find(conference_names) ==
        std::ranges::end(conference_names));

    inline constexpr std::array team_ids
    {
        "ANA"sv,
        "ARI"sv,
        "BOS"sv,
        "BUF"sv,
        "CAR"sv,
        "CBJ"sv,
        "CGY"sv,
        "CHI"sv,
        "COL"sv,
        "DAL"sv,
        "DET"sv,
        "EDM"sv,
        "FLA"sv,
        "LAK"sv,
        "MIN"sv,
        "MTL"sv,
        "NJD"sv,
        "NSH"sv,
        "NYI"sv,
        "NYR"sv,
        "OTT"sv,
        "PHI"sv,
        "PIT"sv,
        "SEA"sv,
        "SJS"sv,
        "STL"sv,
        "TBL"sv,
        "TOR"sv,
        "VAN"sv,
        "VGK"sv,
        "WPG"sv,
        "WSH"sv
    };
    static_assert(team_ids.size() == 32);
    static_assert(std::ranges::is_sorted(team_ids));
    static_assert(std::ranges::adjacent_find(team_ids) ==
        std::ranges::end(team_ids));

    inline constexpr std::array team_names
    {
        "Anaheim Ducks"sv,
        "Arizona Coyotes"sv,
        "Boston Bruins"sv,
        "Buffalo Sabres"sv,
        "Carolina Hurricanes"sv,
        "Columbus Blue Jackets"sv,
        "Calgary Flames"sv,
        "Chicago Blackhawks"sv,
        "Colorado Avalanche"sv,
        "Dallas Stars"sv,
        "Detroit Red Wings"sv,
        "Edmonton Oilers"sv,
        "Florida Panthers"sv,
        "Los Angeles Kings"sv,
        "Minnesota Wild"sv,
        "Montreal Canadiens"sv,
        "New Jersey Devils"sv,
        "Nashville Predators"sv,
        "New York Islanders"sv,
        "New York Rangers"sv,
        "Ottawa Senators"sv,
        "Philadelphia Flyers"sv,
        "Pittsburgh Penguins"sv,
        "Seattle Kraken"sv,
        "San Jose Sharks"sv,
        "St. Louis Blues"sv,
        "Tampa Bay Lightning"sv,
        "Toronto Maple Leafs"sv,
        "Vancouver Canucks"sv,
        "Vegas Golden Knights"sv,
        "Winnipeg Jets"sv,
        "Washington Capitals"sv
    };
    static_assert(std::ranges::size(team_names) == 32);
    static_assert(std::ranges::adjacent_find(team_names) ==
        std::ranges::end(team_names));
    //static_assert(std::ranges::is_sorted(team_names));

    inline constexpr std::array division_ids
    {
        "ATL"sv,
        "CEN"sv,
        "MET"sv,
        "PAC"sv
    };
    static_assert(std::ranges::size(division_ids) == 4);
    static_assert(std::ranges::adjacent_find(division_ids) ==
        std::ranges::end(division_ids));
    static_assert(std::ranges::is_sorted(division_ids));

    inline constexpr std::array division_names
    {
        "Atlantic"sv,
        "Central"sv,
        "Metropolitan"sv,
        "Pacific"sv
    };
    static_assert(std::ranges::size(division_names) == 4);
    static_assert(std::ranges::adjacent_find(division_names) ==
        std::ranges::end(division_names));
    static_assert(std::ranges::is_sorted(division_names));
}
