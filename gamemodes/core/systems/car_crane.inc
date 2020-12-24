#include <YSI_Coding\y_hooks>

static
    gCarCrane,
    gCarPrice[MAX_VEHICLES],
    Float:gCarLastPos[MAX_VEHICLES][4],
    gPlayerTimer[MAX_PLAYERS]
;

hook OnPlayerConnect(playerid)
{
    gPlayerTimer[playerid] = 0;
    return 1;
}

hook OnGameModeInit()
{
    gCarCrane = CreateDynamicCP(2791.0417,-2344.0586,13.6328, 5.0, 0, 0);
    return 1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid)
{
    if(checkpointid == gCarCrane)
    {
        if(Player_GetJob(playerid) == TYPE_MECHANIC && IsPlayerInAnyVehicle(playerid)) {
            SendServerMsgF(playerid, "Press "C_YELLOW"Y"C_WHITE" to sell this car for $%d", gCarPrice[GetPlayerVehicleID(playerid)]);
        } else if(Player_GetJob(playerid) != TYPE_MECHANIC) {
            SendServerMsg(playerid, "Only Mechanics can sell cars here");
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(PRESSED(KEY_YES))
    {
        if(IsPlayerInDynamicCP(playerid, gCarCrane))
        {
            if(Player_GetJob(playerid) != TYPE_MECHANIC) {
                return SendErrorMsg(playerid, "Only Mechanics can sell vehicles");
            }
            if(gettime() < gPlayerTimer[playerid]) {
                return SendErrorMsgF(playerid, "You need to wait %d before selling another vehicle", (gettime() - gPlayerTimer[playerid]));
            }
            new carid = GetPlayerVehicleID(playerid);
            GivePlayerMoney(playerid, gCarPrice[carid]);
            gPlayerTimer[playerid] = gettime() + (60 * 5);
            RespawnCar(carid);
        }
    }
    return 1;
}

RespawnCar(vehicleid)
{
    new modelid = GetVehicleModel(vehicleid);
    CreateCar(modelid, gCarLastPos[vehicleid][0], gCarLastPos[vehicleid][1], gCarLastPos[vehicleid][2], gCarLastPos[vehicleid][3], -1, -1);
    DestroyVehicle(vehicleid);
}

CreateCar(modelid, Float:x, Float:y, Float:z, Float:rotation, color1, color2)
{
    new carid = AddStaticVehicleEx(modelid, x, y, z, z, color1, color2, (60*60), 1);
    new rand = randomEx(50000, 90000);
    gCarPrice[carid] = rand;
    gCarLastPos[carid][0] = x;
    gCarLastPos[carid][1] = y;
    gCarLastPos[carid][2] = z;
    gCarLastPos[carid][3] = rotation;
    return carid;
}