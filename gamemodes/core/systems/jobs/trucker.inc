#include <YSI_Coding\y_hooks>

#define MAX_DELIVERY_NAME       (30)

static enum {
    STATE_PICKUP = 0,
    STATE_DELIVER
}

static
    Timer:TruckingPickupTimer[MAX_PLAYERS],
    Timer:TruckingDeliveryTimer[MAX_PLAYERS]
;

static
    bool:IsPlayerTrucking[MAX_PLAYERS],
    TruckingCooldown[MAX_PLAYERS],
    bool:PlayerCanTruck[MAX_PLAYERS],
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
    if(!PlayerCanTruck[playerid]) {
        return SendErrorMsg(playerid, "You're not in a truck!");
    }
    if(Player_GetWantedLevel(playerid) != 0) {
        return SendErrorMsg(playerid, "Only innocents can start a trucking mission");
    }
    if(Player_GetClass(playerid) != TEAM_CIVILIAN) {
        return SendErrorMsg(playerid, "Only Civilians can start a trucking mission");
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
    SetPlayerRaceCheckpoint(playerid, CP_TYPE_GROUND_FINISH, 2174.6182, -2266.6165, 13.3797, 2174.6182, -2266.6165, 13.3797, 3.0);

    UI_TimeLeft(playerid, 300);
    TruckingPickupTimer[playerid] = defer TruckingPickup(playerid);

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
    SetPlayerRaceCheckpoint(playerid, CP_TYPE_GROUND_FINISH, x, y, z, x, y, z, 3.0);

	stop TruckingPickupTimer[playerid];
    UI_TimeLeft(playerid, 300);
    TruckingDeliveryTimer[playerid] = defer TruckingDelivery(playerid);

    SendServerMsgF(playerid, "Go to %s and deliver the goods", storeName);
    SendServerMsg(playerid, "On Duty!, don't exit the vehicle!");
    return 1;
}

Trucker_End(playerid) {
    IsPlayerTrucking[playerid] = false;
    TruckingCooldown[playerid] = gettime() + 20;

    DisablePlayerRaceCheckpoint(playerid);
    UI_HideTimeLeft(playerid);
    stop TruckingDeliveryTimer[playerid];
    stop TruckingPickupTimer[playerid];
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
            stop TruckingDeliveryTimer[playerid];
        }
        if(PlayerTruckingState[playerid] == STATE_PICKUP) {
            SendServerMsg(playerid, "The staff is putting the goods in your truck!");
            UI_TimeLeft(playerid, 10);
            TogglePlayerControllable(playerid, false);
            defer TruckingStandBy(playerid);
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
        if(PlayerCanTruck[playerid]) {
            PlayerCanTruck[playerid] = false;
        }
    }
    if(newstate == PLAYER_STATE_DRIVER) {
        new pvehid = GetPlayerVehicleID(playerid);
        if(GetVehicleModel(pvehid) == 414) {
            defer TruckerMsg(playerid);
        }
    }
    return 1;
}

timer TruckingPickup[300000](playerid)
{
    SendServerMsg(playerid, "You have failed to pickup the goods");
    Trucker_End(playerid);
}

timer TruckingDelivery[300000](playerid)
{
    SendServerMsg(playerid, "You have failed to deliver the goods");
    Trucker_End(playerid);
}

timer TruckingStandBy[10000](playerid)
{
    Trucker_Begin(playerid);
    TogglePlayerControllable(playerid, true);
}

timer TruckerMsg[1000](playerid)
{
    SendServerMsg(playerid, "Use /trucker to start a trucker mission");
    PlayerCanTruck[playerid] = true;
}