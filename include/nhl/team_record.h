#pragma once

#include <fmt/format.h>
#include "team.h"

namespace nhl
{
    struct team_record
    {
        team_id id;
        int games_played{ 0 };
        int wins{ 0 };
        int losses{ 0 };
        int overtime_losses{ 0 };
        int regulation_wins{ 0 };
        int regulation_or_overtime_wins{ 0 };
        int shootout_wins{ 0 };
        int shootout_losses{ 0 };
        int goals_for{ 0 };
        int goals_against{ 0 };
    };

    inline std::ostream& operator<<(std::ostream& os, team_record const& r)
    {
        auto s = fmt::format(
            "{:^3} {:^3} {:^3} {:^3} {:^3} {:^3} {:^3} {:^3} {:^3} {:^3} {:^3}",
            to_string(r.id),
            r.games_played,
            r.wins,
            r.losses,
            r.overtime_losses,
            r.regulation_wins,
            r.regulation_or_overtime_wins,
            r.shootout_wins,
            r.shootout_losses,
            r.goals_for,
            r.goals_against
        );

        os << s;
        return os;
    }
}

template <>
struct fmt::formatter<nhl::team_record> : fmt::formatter<std::string>
{
    auto format(nhl::team_record const& r, fmt::format_context& ctx)
    {
        return formatter<std::string>::format(
            fmt::format("{:^3} {:^3} {:^3} {:^3} {:^3} {:^3} {:^3} {:^3} {:^3} {:^3} {:^3}",
                to_string(r.id),
                r.games_played,
                r.wins,
                r.losses,
                r.overtime_losses,
                r.regulation_wins,
                r.regulation_or_overtime_wins,
                r.shootout_wins,
                r.shootout_losses,
                r.goals_for,
                r.goals_against),
            ctx);
    }
};
