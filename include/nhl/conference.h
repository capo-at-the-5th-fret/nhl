#pragma once

#include <string_view>
#include "division.h"
#include "nhl/text_literals.h"

namespace nhl
{
    enum class conference_id
    {
        east,
        west
    };

    struct conference_id_values
    {
        static constexpr bool ok(conference_id id) noexcept
        {
            return id >= (min)() && id <= (max)();
        }

        static constexpr conference_id (min)() noexcept
        {
            return conference_id::east;
        }

        static constexpr conference_id (max)() noexcept
        {
            return conference_id::west;
        }
    };

    inline constexpr std::string_view to_string(conference_id id)
    {
        return conference_id_values::ok(id) ?
            text_literals::conference_ids[static_cast<std::size_t>(id)] :
            nhl::text_literals::unknown;
    }

    struct conference
    {
        conference_id id;
        std::array<division_id, 2> divisions;
    };

    namespace conferences
    {
        inline constexpr conference eastern
        {
            conference_id::east,
            { division_id::atlantic, division_id::metropolitan }
        };

        inline constexpr conference western
        {
            conference_id::west,
            { division_id::central, division_id::pacific }
        };
    }
}
