#include <YSI_Coding\y_hooks>

#define MAX_DELIVERY_NAME       (30)

new IsPlayerTrucking[MAX_PLAYERS];
new TruckingCooldown[MAX_PLAYERS];
new PlayerCanTruck[MAX_PLAYERS];
new IsPlayerGettingGoods[MAX_PLAYERS];
new IsPlayerDeliveringGoods[MAX_PLAYERS];

enum Delivery_Datas
{
    STORE_DELIVERY_NAME[MAX_DELIVERY_NAME],
    Float:DCP[4],
}

static
    const DeliverData[][Delivery_Datas] =
{
    {"Disco", {1821.5656, -1682.2516, 13.3828}},
    {"LSPD", {1535.8329, -1673.7499, 13.3828}},
    {"LS BANK", {590.8960, -1231.8680, 17.7482}},
    {"Ammunation Plaza", { 1358.8153, -1278.5531, 13.3517}}
};

CMD:trucker(playerid) {
    if(PlayerCanTruck[playerid] == 1)
    {
        StartPickup(playerid);
    }
    else if(!IsPlayerInVehicle(playerid, 414)) return SendServerMsg(playerid, "You're not in a truck!");
    return 1;
}

stock StartPickup(playerid) {
    if(TruckingCooldown[playerid] == 1) return SendServerMsg(playerid, "Please wait before starting a trucking mission again!");
    IsPlayerTrucking[playerid] = 1;
    IsPlayerGettingGoods[playerid] = 1;
    DisablePlayerRaceCheckpoint(playerid);
    SetPlayerRaceCheckpoint(playerid, 1, 2174.6182, -2266.6165, 13.3797, 2174.6182, -2266.6165, 13.3797, 3.0);
    return 1;
}

stock StartWork(playerid) {
    IsPlayerGettingGoods[playerid] = 0;
    IsPlayerDeliveringGoods[playerid] = 1;
    new randloc = random(sizeof(DeliverData));
    new
        Float:TruckerCp[4],
        Store_Name;
    TruckerCp[0] = DeliverData[randloc][DCP][0];
    TruckerCp[1] = DeliverData[randloc][DCP][1];
    TruckerCp[2] = DeliverData[randloc][DCP][2];
    Store_Name = DeliverData[randloc][STORE_DELIVERY_NAME];
    DisablePlayerRaceCheckpoint(playerid);
    SetPlayerRaceCheckpoint(playerid, 1, TruckerCp[0], TruckerCp[1], TruckerCp[2], TruckerCp[0], TruckerCp[1], TruckerCp[2], 3.0);
    SendServerMsgF(playerid, "Go to %s and deliver goods", Store_Name);
    SendServerMsg(playerid, "On Duty!, Don't exit the vehicle!");
    return 1;
}

stock StopWork(playerid) {
    IsPlayerTrucking[playerid] = 0;
    DisablePlayerRaceCheckpoint(playerid);
    TruckingCooldown[playerid] = 1;
    SetTimerEx("TruckingCD", 20000, false, "i", playerid);
    return 1;
}

hook OnPlayerEnterRaceCP(playerid) 
{
    if(IsPlayerDeliveringGoods[playerid] == 1) {
        new randm = random(50000);
        if(IsPlayerTrucking[playerid] == 1)
        {
            GivePlayerMoney(playerid, randm);
            StopWork(playerid);
            SendServerMsg(playerid, "You've finished trucking!");
            SendServerMsgF(playerid, "And The Store gave you %d!", randm);
        }
    }
    if(IsPlayerGettingGoods[playerid] == 1) {
        StartWork(playerid);
    }
    else return 0;
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_ONFOOT)
    {
        if(IsPlayerTrucking[playerid] == 1)
        {
            SendServerMsg(playerid, "Failed! you've exited the vehicle!");
            StopWork(playerid);
        }
        else
        {
            PlayerCanTruck[playerid] = 0;
        }
    }
    return 1;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
    if(GetVehicleModel(vehicleid) == 414)
    {
        PlayerCanTruck[playerid] = 1;
        SendServerMsg(playerid, "Use /trucker to start a trucker mission");
    }
    return 1;
}

forward TruckingCD(playerid);
public TruckingCD(playerid)
{
    TruckingCooldown[playerid] = 0;
    return 1;
}

CMD:canitruck(playerid) {
    if(PlayerCanTruck[playerid] == 1)
    {
        SendServerMsg(playerid, "Yes you can truck");
    }
    else if(PlayerCanTruck[playerid] == 0)
    {
        SendServerMsg(playerid, "No you can't truck");
    }
    return 1;
}

CMD:givetruck(playerid) {
    new Float:pos[4];
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
    GetPlayerFacingAngle(playerid, pos[3]);
    CreateVehicle(414, pos[0], pos[1], pos[2], pos[3], 0, 0, -1, 0);
    return 1;
}

CMD:car(playerid) {
    new Float:pos[4];
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
    GetPlayerFacingAngle(playerid, pos[3]);
    CreateVehicle(411, pos[0], pos[1], pos[2], pos[3], 0, 0, -1, 0);
    return 1;
}
