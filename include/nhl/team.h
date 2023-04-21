#pragma once

#include <iostream>
#include "nhl/text_literals.h"

namespace nhl
{
    enum class team_id
    {
        ana,
        ari,
        bos,
        buf,
        car,
        cbj,
        cgy,
        chi,
        col,
        dal,
        det,
        edm,
        fla,
        lak,
        min,
        mtl,
        njd,
        nsh,
        nyi,
        nyr,
        ott,
        phi,
        pit,
        sea,
        sjs,
        stl,
        tbl,
        tor,
        van,
        vgk,
        wpg,
        wsh
    };

    struct team_id_values
    {
        static constexpr bool ok(team_id id) noexcept
        {
            return id >= (min)() && id <= (max)();
        }

        static constexpr team_id (min)() noexcept
        {
            return team_id::ana;
        }

        static constexpr team_id (max)() noexcept
        {
            return team_id::wsh;
        }
    };

    inline constexpr std::string_view to_string(team_id id) noexcept
    {
        return team_id_values::ok(id) ?
            text_literals::team_ids[static_cast<std::size_t>(id)] :
            nhl::text_literals::unknown;
    }

    inline std::ostream& operator<<(std::ostream& os, team_id id)
    {
        os << to_string(id);
        return os;
    }

    struct team
    {
        team_id id;
        std::string_view name;
    };

    // FIX: Use text literals for names
    inline constexpr std::array teams
    {
        team{ team_id::ana, "Anaheim Ducks" },
        team{ team_id::ari, "Arizona Coyotes" },
        team{ team_id::bos, "Boston Bruins" },
        team{ team_id::buf, "Buffalo Sabres" },
        team{ team_id::car, "Carolina Hurricanes" },
        team{ team_id::cbj, "Columbus Blue Jackets" },
        team{ team_id::cgy, "Calgary Flames" },
        team{ team_id::chi, "Chicago Blackhawks" },
        team{ team_id::col, "Colorado Avalanche" },
        team{ team_id::dal, "Dallas Stars" },
        team{ team_id::det, "Detroit Red Wings" },
        team{ team_id::edm, "Edmonton Oilers" },
        team{ team_id::fla, "Florida Panthers" },
        team{ team_id::lak, "Los Angeles Kings" },
        team{ team_id::min, "Minnesota Wild" },
        team{ team_id::mtl, "Montreal Canadiens" },
        team{ team_id::njd, "New Jersey Devils" },
        team{ team_id::nsh, "Nashville Predators" },
        team{ team_id::nyi, "New York Islanders" },
        team{ team_id::nyr, "New York Rangers" },
        team{ team_id::ott, "Ottawa Senators" },
        team{ team_id::phi, "Philadelphia Flyers" },
        team{ team_id::pit, "Pittsburgh Penguins" },
        team{ team_id::sea, "Seattle Kraken" },
        team{ team_id::sjs, "San Jose Sharks" },
        team{ team_id::stl, "St. Louis Blues" },
        team{ team_id::tbl, "Tampa Bay Lightning" },
        team{ team_id::tor, "Toronto Maple Leafs" },
        team{ team_id::van, "Vancouver Canucks" },
        team{ team_id::vgk, "Vegas Golden Knights" },
        team{ team_id::wpg, "Winnipeg Jets" },
        team{ team_id::wsh, "Washington Capitals" }
    };
    static_assert(teams.size() == 32);
// #if __cpp_lib_ranges
//     static_assert(std::ranges::is_sorted(teams, {}, &team::id));
// #endif

    constexpr team lookup(team_id id)
    {
        struct teams_sort_by_team_id
        {
            bool operator()(const team& lhs, const team& rhs) const
            {
                return lhs.id < rhs.id;
            }
            bool operator()(const team& lhs, const team_id& rhs) const
            {
                return lhs.id < rhs;
            }
            bool operator()(const team_id& lhs, const team& rhs) const
            {
                return lhs < rhs.id;
            }
        };

        if (auto pos = std::lower_bound(teams.begin(), teams.end(), id,
            teams_sort_by_team_id{}); pos != teams.end() && pos->id == id)
        {
            return *pos;
        }

        // if (auto pos = std::ranges::lower_bound(teams, id, {}, &team::id);
        //     pos != std::ranges::end(teams) && pos->id == id)
        // {
        //     return *pos;
        // }

        throw std::out_of_range("Invalid team id");
    }

}
