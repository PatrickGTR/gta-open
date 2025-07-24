#include <YSI_Coding\y_hooks>

#define MAX_PDELIVERY_NAME       (30)

static enum {
    STATE_PICKUP = 0,
    STATE_DELIVER
}

static
    Timer:PizzaPickupTimer[MAX_PLAYERS],
    Timer:PizzaDeliveryTimer[MAX_PLAYERS];

static
    bool:IsPlayerPDelivering[MAX_PLAYERS],
    PDeliverCooldown[MAX_PLAYERS],
    bool:PlayerCanPDeliver[MAX_PLAYERS],
    PlayerPDeliveringState[MAX_PLAYERS];

enum PIZZA_DELIVERY_DATA {
    F_STORE[MAX_PDELIVERY_NAME],
    Float:F_STORE_X,
    Float:F_STORE_Y,
    Float:F_STORE_Z
}

static
    const DeliverData[][PIZZA_DELIVERY_DATA] = {
    {"LSPD", 1535.8329, -1673.7499, 13.3828},
    {"LS BANK", 590.8960, -1231.8680, 17.7482},
    {"Ammunation Plaza", 1358.8153, -1278.5531, 13.3517},
    {"Idlewood Fuelstation", 1936.578247, -1777.193237, 12.95578},
	{"Alhambra Club", 1831.819580, -1682.267456, 13.11395},
	{"CJ House", 2495.337402, -1684.785644, 13.03212},
	{"Los Santos Race Arena", 2726.939208, -1851.421264, 9.146192},
	{"Willowfield Mod Garage", 2644.418457, -2034.457031, 13.12427},
	{"Willowfield Ammunation", 2399.982910, -1976.935302, 12.95189},
	{"Casa De Empeno", 2144.479980, -1901.673461, 13.11519},
	{"The Mexican Bar", 1955.709838, -2004.178222, 13.11948},
	{"24/7", 1829.145874, -1842.526489, 13.13035},
	{"Unity Station", 1743.641601, -1861.159790, 13.14912},
	{"Donut Shop", 1038.441650, -1337.099121, 13.29034},
	{"Gnocchi", 553.708984, -1473.299804, 14.33577},
	{"Italian Store", 479.580139, -1533.522949, 19.26560},
	{"The Book Emporium", 832.689575, -1598.760498, 13.12357}
};

timer PDeliveringPickup[300000](playerid) {
    SendMsgF(playerid, COLOR_RED, "(pizza delivery) "C_WHITE"You have failed to pickup the goods");
    Trucker_End(playerid);
}

/*timer PDelivery[300000](playerid) {
    SendMsgF(playerid, COLOR_RED, "(pizza delivery) "C_WHITE"You have failed to deliver the goods.");
    Trucker_End(playerid);
}*/

timer PDeliveryMsg[1000](playerid) {
    SendServerMsg(playerid, "Use /pdelivery to start a Pizza delivery men mission");
    PlayerCanPDeliver[playerid] = true;
}

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
    SetPlayerRaceCheckpoint(playerid, CP_TYPE_GROUND_FINISH, 2115.5190, -1788.4954, 13.5547, 2115.5190, -1788.4954, 13.5547, 3.0);

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
    SetPlayerRaceCheckpoint(playerid, CP_TYPE_GROUND_FINISH, x, y, z, x, y, z, 3.0);

    stop PizzaPickupTimer[playerid];
    UI_TimeLeft(playerid, 300);
    PizzaDeliveryTimer[playerid] = defer TruckingDelivery(playerid);

    SendMsgF(playerid, COLOR_RED, "(pizza delivery) "C_WHITE"On duty, do not exit the vehicle. Deliver pizza to "C_RED"%s", storeName);
    return 1;
}

Pizza_End(playerid) {
    // Reset all the data
    IsPlayerPDelivering[playerid] = false;
    PDeliverCooldown[playerid] = gettime() + 20;
    DisablePlayerRaceCheckpoint(playerid);
    UI_HideTimeLeft(playerid);
    stop PizzaDeliveryTimer[playerid];
    stop PizzaPickupTimer[playerid];

    // Reward Player
    new reward = random(500) + 250;
    GivePlayerMoney(playerid, reward);

    // Notify Player
    SendMsgF(playerid, COLOR_RED, "(pizza delivery) "C_WHITE"Pizza successfully delivered!");
    return 1;
}

hook OnPlayerEnterRaceCP(playerid) {
    if(IsPlayerPDelivering[playerid]) {
        if(PlayerPDeliveringState[playerid] == STATE_DELIVER) {
            Pizza_End(playerid);
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
            SendMsgF(playerid, COLOR_RED, "(pizza delivery) "C_WHITE"Pizza delivery failed, exited the vehicle.");

            Pizza_End(playerid);
        }
        if(PlayerCanPDeliver[playerid]) {
            PlayerCanPDeliver[playerid] = false;
        }
    }
    if(newstate == PLAYER_STATE_DRIVER) {
        new vehicleid = GetPlayerVehicleID(playerid);
        if(GetVehicleModel(vehicleid) == 448) {
            defer PDeliveryMsg(playerid);
        }
    }
    return 1;
}