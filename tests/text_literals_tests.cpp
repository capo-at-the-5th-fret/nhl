#include <doctest/doctest.h>
#include "nhl/text_literals.h"

TEST_CASE("text_literals")
{
    SUBCASE("team_ids")
    {
        using nhl::text_literals::team_ids;

        static_assert(team_ids.size() == 32);
        static_assert(team_ids[0] == "ANA");
        static_assert(team_ids[1] == "ARI");
        static_assert(team_ids[2] == "BOS");
        static_assert(team_ids[3] == "BUF");
        static_assert(team_ids[4] == "CAR");
        static_assert(team_ids[5] == "CBJ");
        static_assert(team_ids[6] == "CGY");
        static_assert(team_ids[7] == "CHI");
        static_assert(team_ids[8] == "COL");
        static_assert(team_ids[9] == "DAL");
        static_assert(team_ids[10] == "DET");
        static_assert(team_ids[11] == "EDM");
        static_assert(team_ids[12] == "FLA");
        static_assert(team_ids[13] == "LAK");
        static_assert(team_ids[14] == "MIN");
        static_assert(team_ids[15] == "MTL");
        static_assert(team_ids[16] == "NJD");
        static_assert(team_ids[17] == "NSH");
        static_assert(team_ids[18] == "NYI");
        static_assert(team_ids[19] == "NYR");
        static_assert(team_ids[20] == "OTT");
        static_assert(team_ids[21] == "PHI");
        static_assert(team_ids[22] == "PIT");
        static_assert(team_ids[23] == "SEA");
        static_assert(team_ids[24] == "SJS");
        static_assert(team_ids[25] == "STL");
        static_assert(team_ids[26] == "TBL");
        static_assert(team_ids[27] == "TOR");
        static_assert(team_ids[28] == "VAN");
        static_assert(team_ids[29] == "VGK");
        static_assert(team_ids[30] == "WPG");
        static_assert(team_ids[31] == "WSH");
    }

    SUBCASE("team_names")
    {
        using nhl::text_literals::team_names;

        static_assert(team_names.size() == 32);
        static_assert(team_names[0] == "Anaheim Ducks");
        static_assert(team_names[1] == "Arizona Coyotes");
        static_assert(team_names[2] == "Boston Bruins");
        static_assert(team_names[3] == "Buffalo Sabres");
        static_assert(team_names[4] == "Carolina Hurricanes");
        static_assert(team_names[5] == "Columbus Blue Jackets");
        static_assert(team_names[6] == "Calgary Flames");
        static_assert(team_names[7] == "Chicago Blackhawks");
        static_assert(team_names[8] == "Colorado Avalanche");
        static_assert(team_names[9] == "Dallas Stars");
        static_assert(team_names[10] == "Detroit Red Wings");
        static_assert(team_names[11] == "Edmonton Oilers");
        static_assert(team_names[12] == "Florida Panthers");
        static_assert(team_names[13] == "Los Angeles Kings");
        static_assert(team_names[14] == "Minnesota Wild");
        static_assert(team_names[15] == "Montreal Canadiens");
        static_assert(team_names[16] == "New Jersey Devils");
        static_assert(team_names[17] == "Nashville Predators");
        static_assert(team_names[18] == "New York Islanders");
        static_assert(team_names[19] == "New York Rangers");
        static_assert(team_names[20] == "Ottawa Senators");
        static_assert(team_names[21] == "Philadelphia Flyers");
        static_assert(team_names[22] == "Pittsburgh Penguins");
        static_assert(team_names[23] == "Seattle Kraken");
        static_assert(team_names[24] == "San Jose Sharks");
        static_assert(team_names[25] == "St. Louis Blues");
        static_assert(team_names[26] == "Tampa Bay Lightning");
        static_assert(team_names[27] == "Toronto Maple Leafs");
        static_assert(team_names[28] == "Vancouver Canucks");
        static_assert(team_names[29] == "Vegas Golden Knights");
        static_assert(team_names[30] == "Winnipeg Jets");
        static_assert(team_names[31] == "Washington Capitals");
    };

}
