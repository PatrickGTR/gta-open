#include <YSI_Coding\y_hooks>

static
    PlayerLastEnteredVehicleID[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
    PlayerLastEnteredVehicleID[playerid] = INVALID_VEHICLE_ID;
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate) {
    if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER) {
        PlayerLastEnteredVehicleID[playerid] = GetPlayerVehicleID(playerid);
    }
    return 1;
}

// API
Player_LastEnteredVehicleID(playerid) {
    return PlayerLastEnteredVehicleID[playerid];
}