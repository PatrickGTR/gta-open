#include <YSI_Coding\y_hooks>

#define MAX_PDELIVERY_NAME       (30)

static enum {
    STATE_PICKUP = 0,
    STATE_DELIVER
}

static
    Timer:PizzaPickupTimer[MAX_PLAYERS],
    Timer:PizzaDeliveryTimer[MAX_PLAYERS]
;

static 
    bool:IsPlayerPDelivering[MAX_PLAYERS], 
    PDeliverCooldown[MAX_PLAYERS],
    bool:PlayerCanPDeliver[MAX_PLAYERS],
    PlayerPDeliveringState[MAX_PLAYERS];

enum F_DELIVERY_DATA
{
    F_STORE[MAX_PDELIVERY_NAME],
    Float:F_STORE_X,
    Float:F_STORE_Y,
    Float:F_STORE_Z
}

static
    const DeliverData[][F_DELIVERY_DATA] =
{
    {"Disco", 1821.5656, -1682.2516, 13.3828},
    {"LSPD", 1535.8329, -1673.7499, 13.3828},
    {"LS BANK", 590.8960, -1231.8680, 17.7482},
    {"Ammunation Plaza", 1358.8153, -1278.5531, 13.3517}
};

CMD:pdelivery(playerid) {
    if(!PlayerCanPDeliver[playerid]) {
        return SendErrorMsg(playerid, "You're not in a Pizzaboy bike!");
    } 
    if(Player_GetWantedLevel(playerid) != 0) {
        return SendErrorMsg(playerid, "Only innocents can start a Pizza delivery mission");
    }
    if(Player_GetClass(playerid) != TEAM_CIVILIAN) {
        return SendErrorMsg(playerid, "Only Civilians can start a Pizza delivery mission");
    }
    Pizza_Pickup(playerid);
    return 1;
}

Pizza_Pickup(playerid) {
    if(gettime() < PDeliverCooldown[playerid]) {
        return SendErrorMsg(playerid, "Please wait before starting a trucking mission again!");
    }
    IsPlayerPDelivering[playerid] = true;
    PlayerPDeliveringState[playerid] = STATE_PICKUP;

    DisablePlayerRaceCheckpoint(playerid);
    SetPlayerRaceCheckpoint(playerid, 1, 2115.5190, -1788.4954, 13.5547, 2115.5190, -1788.4954, 13.5547, 3.0);

    UI_TimeLeft(playerid, 300);
    PizzaPickupTimer[playerid] = defer PDeliveringPickup(playerid);

    SendServerMsg(playerid, "You're Pizza delivering now please pick up the Pizza at the checkpoint!");
    return 1;
}

Pizza_Begin(playerid) {
    PlayerPDeliveringState[playerid] = STATE_DELIVER;
    new randloc = random(sizeof(DeliverData));
    new
        Float:x,
        Float:y,
        Float:z,
        storeName[MAX_DELIVERY_NAME];

    x = DeliverData[randloc][F_STORE_X];
    y = DeliverData[randloc][F_STORE_Y];
    z = DeliverData[randloc][F_STORE_Z];
    strcpy(storeName, DeliverData[randloc][F_STORE], sizeof(storeName));

    DisablePlayerRaceCheckpoint(playerid);
    SetPlayerRaceCheckpoint(playerid, 1, x, y, z, x, y, z, 3.0);

    stop PizzaPickupTimer[playerid];
    UI_TimeLeft(playerid, 300);
    PizzaDeliveryTimer[playerid] = defer TruckingDelivery(playerid);

    SendServerMsgF(playerid, "Go to %s and deliver the pizza!", storeName);
    SendServerMsg(playerid, "On Duty!. don't exit the vehicle!");
    return 1;
}

Pizza_End(playerid) {
    IsPlayerPDelivering[playerid] = false;
    PDeliverCooldown[playerid] = gettime() + 20;

    DisablePlayerRaceCheckpoint(playerid);
    UI_HideTimeLeft(playerid);
    stop PizzaDeliveryTimer[playerid];
    stop PizzaPickupTimer[playerid];
    return 1;
}

hook OnPlayerEnterRaceCP(playerid) 
{
    if(IsPlayerPDelivering[playerid])
    {
        if(PlayerPDeliveringState[playerid] == STATE_DELIVER) {
            new randm = random(50000);
            GivePlayerMoney(playerid, randm);
            Trucker_End(playerid);
            SendServerMsg(playerid, "You've finished delivering the pizza!");
            SendServerMsgF(playerid, "And the Owner gave you $%d!", randm);
            stop PizzaDeliveryTimer[playerid];
        }
        if(PlayerPDeliveringState[playerid] == STATE_PICKUP) {
            Pizza_Begin(playerid);
        }
    }
    
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate) {
    if(newstate == PLAYER_STATE_ONFOOT) {
        if(IsPlayerPDelivering[playerid]) {
            SendServerMsg(playerid, "Failed! you've exited the vehicle!");
            Pizza_End(playerid);
        }
        if(PlayerCanPDeliver[playerid]) {
            PlayerCanPDeliver[playerid] = false;
        }
    }
    if(newstate == PLAYER_STATE_DRIVER) {
        new pvehid = GetPlayerVehicleID(playerid);
        if(GetVehicleModel(pvehid) == 448) {
            defer PDeliveryMsg(playerid);
        }
    }
    return 1;
}

timer PDeliveringPickup[300000](playerid)
{
    SendServerMsg(playerid, "You have failed to pickup the goods");
    Trucker_End(playerid);
}

timer PDelivery[300000](playerid)
{
    SendServerMsg(playerid, "You have failed to deliver the goods");
    Trucker_End(playerid);
}

timer PDeliveryMsg[1000](playerid)
{
    SendServerMsg(playerid, "Use /pdelivery to start a Pizza delivery men mission");
    PlayerCanPDeliver[playerid] = true;
}