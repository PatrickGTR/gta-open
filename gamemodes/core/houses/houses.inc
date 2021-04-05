#include <houses_empty-interior>
#include <houses_interior-data>
#include <houses_impl>
#include <houses_entext-handler>
#include <houses_cmd>
#include <houses_lock>

#include <furniture>

#include <YSI_Coding\y_hooks>

enum E_QUOTE_DATA {
    E_QUOTE_CONTENT,
    E_QUOTE_AUTHOR
}

// Thanks to https://www.quoteambition.com/home-quotes/
// ligthen the player's mood with nice messages once
// they have entered their house.
static const HomeQuotes[][E_QUOTE_DATA][] = {
    {"Home is where I work, and I work everywhere.", "Alfred Nobel"},
    {"A home without books is a body without soul.", "Marcus Tullius Cicero"},
    {"Home is a shelter from storms all sorts of storms.", "William J. Bennett"},
    {"Home is everything you can walk to.", "Jerry Spinelli"},
    {"I want my home to be that kind of place a place of sustenance, a place of invitation, a place of welcome.", "Mary DeMuth"},
    {"They created a home where I felt safe. I could make mistakes. Failure wasn not punished.", "Sarah Williams"},
    {"Spend some time this weekend on home improvement; improve your attitude toward your family.", "Bo Bennett"},
    {"Home is where you feel at home and are treated well.", "Dalai Lama"},
    {"Where thou art, that is home.", "Emily Dickinson"},
    {"Home is where one starts from.", "T. S. Eliot"}
};

static
    BitArray: PlayerInsideAHouse<MAX_PLAYERS>;

stock Player_IsInsideHouse(playerid) {
    return Bit_Get(PlayerInsideAHouse, playerid);
}

hook OnPlayerConnect(playerid) {
    Bit_Set(PlayerInsideAHouse, playerid, false);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if(PRESSED(KEY_NO) && Player_IsInsideHouse(playerid)) {
        return CommandExecute(playerid, "furniture");
    }

    if(PRESSED(KEY_SECONDARY_ATTACK)) {
        new
            houseid = Player_GetInHouseID(playerid);
        if(Player_InHouseEntrance(playerid, houseid)) {
            if(
                (House_PlayerIsOwner(playerid, houseid) && House_IsLocked(houseid))
                || !House_IsLocked(houseid)
            ) {

                new
                    homeMessage[256];

                new
                    idx = clamp(random(sizeof(HomeQuotes)), 0, sizeof(HomeQuotes));

                strcat(homeMessage, "\"");
                strcat(homeMessage, HomeQuotes[idx][E_QUOTE_CONTENT]);
                strcat(homeMessage, "\"");

                strcat(homeMessage, "~n~");
                strcat(homeMessage, "-");
                strcat(homeMessage, " ");
                strcat(homeMessage, "~y~");
                strcat(homeMessage, HomeQuotes[idx][E_QUOTE_AUTHOR]);

                strcat(homeMessage, "~n~~n~");
                strcat(homeMessage, "~w~You can press ~r~N ~w~to open furniture menu.");

                MessageBox_Show(
                    playerid,
                    TYPE_MSGBOX,
                    "~g~Welcome home!",
                    homeMessage
                );

                new
                    Float: x,
                    Float: y,
                    Float: z,
                    interiorid,
                    bool:unused;

                House_GetInteriorData(
                    House_GetInterior(houseid),
                    x,
                    y,
                    z,
                    interiorid,
                    unused,
                    unused
                );

                SetPlayerInterior(playerid, interiorid);
                SetPlayerVirtualWorld(playerid, House_GetWorld(houseid));
                SetPlayerPos(playerid, x, y, z);
                SetCameraBehindPlayer(playerid);

                Bit_Set(PlayerInsideAHouse, playerid, true);
            }
        }

        if(Player_InHouseExit(playerid, houseid)) {

            if(!(Player_IsInsideHouse(playerid))) {
                return 1;
            }

            if (Player_IsOnFurnitureMode(playerid)) {
                return 1;
            }

            MessageBox_Show(
                playerid,
                TYPE_MSGBOX,
                "~r~Goodbye",
                "See you soon."
            );

            new
                Float: x,
                Float: y,
                Float: z,
                Float: a;

            House_GetEntranceData(houseid, x, y, z, a);

            SetPlayerInterior(playerid, 0);
            SetPlayerVirtualWorld(playerid, 0);
            SetPlayerPos(playerid, x, y, z);
            SetPlayerFacingAngle(playerid, a);

            Bit_Set(PlayerInsideAHouse, playerid, false);
        }
    }
    return 1;
}