#include <houses_empty-interior>
#include <houses_interior-data>
#include <houses_impl>
#include <houses_entext-handler>
#include <houses_cmd>

#if SETUP_TABLE
    #include <houses_setup-table>
#endif

#include <furniture>

#include <YSI_Coding\y_hooks>

static
    BitArray: PlayerInsideAHouse<MAX_PLAYERS>;

stock Player_IsInsideHouse(playerid) {
    return Bit_Get(PlayerInsideAHouse, playerid);
}

hook OnPlayerConnect(playerid) {
    Bit_Set(PlayerInsideAHouse, playerid, false);
    return 1;
}

hook OnMySQLConnected() {
    House_Load();
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if(PRESSED(KEY_SECONDARY_ATTACK)) {
        new
            houseid = Player_GetInHouseID(playerid);
        if(Player_InHouseEntrance(playerid, houseid)) {
            if(House_PlayerIsOwner(playerid, houseid)) {
                MessageBox_Show(
                    playerid,
                    TYPE_MSGBOX,
                    "~g~Welcome home!",
                    "Home is where the heart is."
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