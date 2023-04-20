#include <doctest/doctest.h>
#include "nhl/team.h"

TEST_CASE("team_id_values")
{
    using namespace nhl;

    static_assert((team_id_values::min)() == team_id::ana);
    static_assert((team_id_values::max)() == team_id::wsh);

    static_assert(team_id_values::ok(team_id::ana));
    static_assert(team_id_values::ok(team_id::ari));
    static_assert(team_id_values::ok(team_id::bos));
    static_assert(team_id_values::ok(team_id::buf));
    static_assert(team_id_values::ok(team_id::car));
    static_assert(team_id_values::ok(team_id::cbj));
    static_assert(team_id_values::ok(team_id::cgy));
    static_assert(team_id_values::ok(team_id::chi));
    static_assert(team_id_values::ok(team_id::col));
    static_assert(team_id_values::ok(team_id::dal));
    static_assert(team_id_values::ok(team_id::det));
    static_assert(team_id_values::ok(team_id::edm));
    static_assert(team_id_values::ok(team_id::fla));
    static_assert(team_id_values::ok(team_id::lak));
    static_assert(team_id_values::ok(team_id::min));
    static_assert(team_id_values::ok(team_id::mtl));
    static_assert(team_id_values::ok(team_id::njd));
    static_assert(team_id_values::ok(team_id::nsh));
    static_assert(team_id_values::ok(team_id::nyi));
    static_assert(team_id_values::ok(team_id::nyr));
    static_assert(team_id_values::ok(team_id::ott));
    static_assert(team_id_values::ok(team_id::phi));
    static_assert(team_id_values::ok(team_id::pit));
    static_assert(team_id_values::ok(team_id::sea));
    static_assert(team_id_values::ok(team_id::sjs));
    static_assert(team_id_values::ok(team_id::stl));
    static_assert(team_id_values::ok(team_id::tbl));
    static_assert(team_id_values::ok(team_id::tor));
    static_assert(team_id_values::ok(team_id::van));
    static_assert(team_id_values::ok(team_id::vgk));
    static_assert(team_id_values::ok(team_id::wpg));
    static_assert(team_id_values::ok(team_id::wsh));

    static_assert(!team_id_values::ok(static_cast<team_id>(
        static_cast<int>((team_id_values::max)()) + 1)));
}

TEST_CASE("team_id")
{
    using nhl::team_id;
    using enum nhl::team_id;

    using underlying_t = std::underlying_type_t<team_id>;
    static_assert(std::is_same_v<underlying_t, int>);

    static_assert(std::to_underlying(ana) == 0);
    static_assert(std::to_underlying(ari) == 1);
    static_assert(std::to_underlying(bos) == 2);
    static_assert(std::to_underlying(buf) == 3);
    static_assert(std::to_underlying(car) == 4);
    static_assert(std::to_underlying(cbj) == 5);
    static_assert(std::to_underlying(cgy) == 6);
    static_assert(std::to_underlying(chi) == 7);
    static_assert(std::to_underlying(col) == 8);
    static_assert(std::to_underlying(dal) == 9);
    static_assert(std::to_underlying(det) == 10);
    static_assert(std::to_underlying(edm) == 11);
    static_assert(std::to_underlying(fla) == 12);
    static_assert(std::to_underlying(lak) == 13);
    static_assert(std::to_underlying(min) == 14);
    static_assert(std::to_underlying(mtl) == 15);
    static_assert(std::to_underlying(njd) == 16);
    static_assert(std::to_underlying(nsh) == 17);
    static_assert(std::to_underlying(nyi) == 18);
    static_assert(std::to_underlying(nyr) == 19);
    static_assert(std::to_underlying(ott) == 20);
    static_assert(std::to_underlying(phi) == 21);
    static_assert(std::to_underlying(pit) == 22);
    static_assert(std::to_underlying(sea) == 23);
    static_assert(std::to_underlying(sjs) == 24);
    static_assert(std::to_underlying(stl) == 25);
    static_assert(std::to_underlying(tbl) == 26);
    static_assert(std::to_underlying(tor) == 27);
    static_assert(std::to_underlying(van) == 28);
    static_assert(std::to_underlying(vgk) == 29);
    static_assert(std::to_underlying(wpg) == 30);
    static_assert(std::to_underlying(wsh) == 31);

    SUBCASE("to_string")
    {
        static_assert(to_string(ana) == "ANA");
        static_assert(to_string(ari) == "ARI");
        static_assert(to_string(bos) == "BOS");
        static_assert(to_string(buf) == "BUF");
        static_assert(to_string(car) == "CAR");
        static_assert(to_string(cbj) == "CBJ");
        static_assert(to_string(cgy) == "CGY");
        static_assert(to_string(chi) == "CHI");
        static_assert(to_string(col) == "COL");
        static_assert(to_string(dal) == "DAL");
        static_assert(to_string(det) == "DET");
        static_assert(to_string(edm) == "EDM");
        static_assert(to_string(fla) == "FLA");
        static_assert(to_string(lak) == "LAK");
        static_assert(to_string(min) == "MIN");
        static_assert(to_string(mtl) == "MTL");
        static_assert(to_string(njd) == "NJD");
        static_assert(to_string(nsh) == "NSH");
        static_assert(to_string(nyi) == "NYI");
        static_assert(to_string(nyr) == "NYR");
        static_assert(to_string(ott) == "OTT");
        static_assert(to_string(phi) == "PHI");
        static_assert(to_string(pit) == "PIT");
        static_assert(to_string(sea) == "SEA");
        static_assert(to_string(sjs) == "SJS");
        static_assert(to_string(stl) == "STL");
        static_assert(to_string(tbl) == "TBL");
        static_assert(to_string(tor) == "TOR");
        static_assert(to_string(van) == "VAN");
        static_assert(to_string(vgk) == "VGK");
        static_assert(to_string(wpg) == "WPG");
        static_assert(to_string(wsh) == "WSH");

        static_assert(to_string(static_cast<team_id>(100)) == "?");
    }
}