#pragma once

#include <string_view>
#include <array>
#include "nhl/text_literals.h"
#include "team.h"

namespace nhl
{
    enum class division_id
    {
        atlantic,
        central,
        metropolitan,
        pacific
    };

    struct division_id_values
    {
        static constexpr bool ok(division_id id) noexcept
        {
            return id >= (min)() && id <= (max)();
        }

        static constexpr division_id (min)() noexcept
        {
            return division_id::atlantic;
        }

        static constexpr division_id (max)() noexcept
        {
            return division_id::pacific;
        }
    };

    inline constexpr std::string_view to_string(division_id id)
    {
        return division_id_values::ok(id) ?
            text_literals::division_ids[static_cast<std::size_t>(id)] :
            nhl::text_literals::unknown;
    }

    struct division
    {
        division_id id;
        std::array<team_id, 8> teams;
    };

    namespace divisions
    {
        #if 0
        inline constexpr std::array all =
        {
            division
            {
                division_id::atlantic,
                {
                    team_id::bos, team_id::buf, team_id::det, team_id::fla,
                    team_id::mtl, team_id::ott, team_id::tbl, team_id::tor
                }
            },

            division
            {
                division_id::central,
                {
                    team_id::ari, team_id::chi, team_id::col, team_id::dal,
                    team_id::min, team_id::nsh, team_id::stl, team_id::wpg
                }
            },

            division
            {
                division_id::metropolitan,
                {
                    team_id::car, team_id::cbj, team_id::phi, team_id::pit,
                    team_id::njd, team_id::nyi, team_id::nyr, team_id::wsh
                }
            },

            division
            {
                division_id::pacific,
                {
                    team_id::ana, team_id::cgy, team_id::edm, team_id::lak,
                    team_id::sea, team_id::sjs, team_id::van, team_id::vgk
                }
            }
        };
        #endif

        inline constexpr division central
        {
            division_id::central,
            {
                team_id::ari, team_id::chi, team_id::col, team_id::dal,
                team_id::min, team_id::nsh, team_id::stl, team_id::wpg
            }
        };

        inline constexpr division metropolitan
        {
            division_id::metropolitan,
            {
                team_id::car, team_id::cbj, team_id::phi, team_id::pit,
                team_id::njd, team_id::nyi, team_id::nyr, team_id::wsh
            }
        };

        inline constexpr division pacific
        {
            division_id::pacific,
            {
                team_id::ana, team_id::cgy, team_id::edm, team_id::lak,
                team_id::sea, team_id::sjs, team_id::van, team_id::vgk
            }
        };
    }
}
