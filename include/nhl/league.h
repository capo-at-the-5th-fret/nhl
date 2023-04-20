#pragma once

#include <array>
#include "conference.h"

namespace nhl
{
    inline constexpr std::size_t team_count{ 32 };

    struct league
    {
        std::array<conference_id, 2> conferences;
    };

    inline constexpr league nhl
    {
        { conference_id::east, conference_id::west }
    };
}
