#include <YSI_Coding\y_hooks>

#define MAX_DELIVERY_NAME       (30)

static enum {
    STATE_PICKUP = 0,
    STATE_DELIVER
}

static 
    bool:IsPlayerTrucking[MAX_PLAYERS], 
    TruckingCooldown[MAX_PLAYERS],
    PlayerTruckingState[MAX_PLAYERS];

enum E_DELIVERY_DATA
{
    E_STORE[MAX_DELIVERY_NAME],
    Float:E_STORE_X,
    Float:E_STORE_Y,
    Float:E_STORE_Z
}

static
    const DeliverData[][E_DELIVERY_DATA] =
{
    {"Disco", 1821.5656, -1682.2516, 13.3828},
    {"LSPD", 1535.8329, -1673.7499, 13.3828},
    {"LS BANK", 590.8960, -1231.8680, 17.7482},
    {"Ammunation Plaza", 1358.8153, -1278.5531, 13.3517}
};

CMD:trucker(playerid) {
    if(!IsPlayerInVehicle(playerid, 414)) {
        SendErrorMsg(playerid, "You're not in a truck!");
        return 1;
    } 
        
    Trucker_Pickup(playerid);
    return 1;
}

Trucker_Pickup(playerid) {
    if(gettime() < TruckingCooldown[playerid]) {
        return SendErrorMsg(playerid, "Please wait before starting a trucking mission again!");
    }
    IsPlayerTrucking[playerid] = true;
    PlayerTruckingState[playerid] = STATE_PICKUP;
    
    DisablePlayerRaceCheckpoint(playerid);
    SetPlayerRaceCheckpoint(playerid, 1, 2174.6182, -2266.6165, 13.3797, 2174.6182, -2266.6165, 13.3797, 3.0);
    
    SendServerMsg(playerid, "You're trucking now please pick up goods!");
    return 1;
}

Trucker_Begin(playerid) {
    PlayerTruckingState[playerid] = STATE_DELIVER;
    new randloc = random(sizeof(DeliverData));
    new
        Float:x,
        Float:y,
        Float:z,
        storeName[MAX_DELIVERY_NAME];

    x = DeliverData[randloc][E_STORE_X];
    y = DeliverData[randloc][E_STORE_Y];
    z = DeliverData[randloc][E_STORE_Z];
    strcpy(storeName, DeliverData[randloc][E_STORE], sizeof(storeName));

    DisablePlayerRaceCheckpoint(playerid);
    SetPlayerRaceCheckpoint(playerid, 1, x, y, z, x, y, z, 3.0);

    SendServerMsgF(playerid, "Go to %s and deliver the goods", storeName);
    SendServerMsg(playerid, "On Duty!, don't exit the vehicle!");
    return 1;
}

Trucker_End(playerid) {
    IsPlayerTrucking[playerid] = false;
    TruckingCooldown[playerid] = gettime() + 20;

    DisablePlayerRaceCheckpoint(playerid);
    return 1;
}

hook OnPlayerEnterRaceCP(playerid) 
{
    if(IsPlayerTrucking[playerid])
    {
        if(PlayerTruckingState[playerid] == STATE_DELIVER) {
            new randm = random(50000);
            GivePlayerMoney(playerid, randm);
            Trucker_End(playerid);
            SendServerMsg(playerid, "You've finished trucking!");
            SendServerMsgF(playerid, "And The Store gave you %d!", randm);
        }
        if(PlayerTruckingState[playerid] == STATE_PICKUP) {
            Trucker_Begin(playerid);
        }
    }
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate) {
    if(newstate == PLAYER_STATE_ONFOOT) {
        if(IsPlayerTrucking[playerid]) {
            SendServerMsg(playerid, "Failed! you've exited the vehicle!");
            Trucker_End(playerid);
        }
    }
    return 1;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger) {
    if(GetVehicleModel(vehicleid) == 414) {
        SendServerMsg(playerid, "Use /trucker to start a trucker mission");
    }
    return 1;
}

