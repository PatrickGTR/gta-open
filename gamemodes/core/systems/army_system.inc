#include <YSI_Coding\y_hooks>

#define MAX_ARMY_VEHICLES 10

static
    armyVehicles[MAX_ARMY_VEHICLES],
    armyVehicleCount;

stock bool:IsArmyVehicle(vehicleid)
{
    for (new i = 0; i < MAX_ARMY_VEHICLES; i ++)
    {
        if (armyVehicles[i] == vehicleid)
            return true;
    }
    return false;
}

hook OnGameModeInit()
{
    Create3DTextLabel("Press "C_YELLOW"~k~~CONVERSATION_NO~"C_WHITE" to open the gate", COLOR_WHITE, 1240.9739, -2035.3715, 59.9941, 40.0, 0, 0);
    Create3DTextLabel("Press "C_YELLOW"~k~~CONVERSATION_NO~"C_WHITE" to open the gate", COLOR_WHITE, 1086.5114, -2098.7629, 64.5963, 40.0, 0, 0);

    CreateDynamic3DTextLabel("Press "C_YELLOW"~k~~CONVERSATION_YES~"C_WHITE" to see Heal\n\nCost "C_GREEN"$500", COLOR_WHITE, 1157.1663, -2019.1108, 70.1159, 40.0, .testlos = 1);
    CreateActor(274, 1157.1663, -2019.1108, 69.1159, 84.8518);

    // Hydra
    CreateArmyVehicle(520, 1153.7114, -2018.7710, 78.3643, 269.3837, -1, -1);
    CreateArmyVehicle(520, 1155.2183, -2052.3164, 77.8981, 270.8756, -1, -1);

    // Hunters
    CreateArmyVehicle(425, 1116.0020, -2053.7476, 75.0019, 197.8182, -1, -1);
    CreateArmyVehicle(425, 1115.8762, -2019.5090, 75.0043, 208.2099, -1, -1);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(PRESSED(KEY_YES) && Player_GetClass(playerid) == TEAM_ARMY)
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, 1157.1663, -2019.1108, 69.1159)) {
            new
                Float:health;
            GetPlayerHealth(playerid, health);

            if(GetPlayerMoney(playerid) < 500) {
                return SendErrorMsg(playerid, "Not enough money!");
            }

            if(health >= 100) {
                return SendErrorMsg(playerid, "You have full health!");
            }

            GivePlayerMoney(playerid, -500);
            SetPlayerHealth(playerid, 100);
        }
    }
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate) {
    if(newstate == PLAYER_STATE_DRIVER) {
        new
            vehicleid = GetPlayerVehicleID(playerid);

        if(IsArmyVehicle(vehicleid) && Player_GetClass(playerid) != TEAM_ARMY) {
            SendErrorMsg(playerid, "You're not a Army You can't enter this vehicle!");
            RemovePlayerFromVehicle(playerid);
        }
    }
    return 1;
}

hook OnVehicleDeath(vehicleid, killerid) {
    if(IsArmyVehicle(vehicleid)) {
        DestroyVehicle(vehicleid);
        armyVehicleCount --;
    }
    return 1;
}

stock CreateArmyVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2)
{
    new v = AddStaticVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2);
    armyVehicles[armyVehicleCount++] = v;
}