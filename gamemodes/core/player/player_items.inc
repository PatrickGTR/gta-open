static
    PlayerC4[MAX_PLAYERS],
    PlayerCrack[MAX_PLAYERS],
    PlayerWeed[MAX_PLAYERS],
    PlayerPickLock[MAX_PLAYERS],
    PlayerWallet[MAX_PLAYERS],
    PlayerCondom[MAX_PLAYERS],
    PlayerRope[MAX_PLAYERS],
    PlayerScissors[MAX_PLAYERS];

#include <YSI_Coding\y_hooks>

hook OnPlayerConnect(playerid) {
    PlayerC4[playerid] =
    PlayerWeed[playerid] =
    PlayerPickLock[playerid] =
    PlayerWallet[playerid] =
    PlayerRope[playerid] =
    PlayerCondom[playerid] =
    PlayerScissors[playerid] =
    PlayerCrack[playerid] = 0;
}

stock Player_GetC4(playerid) {
    return PlayerC4[playerid];
}

stock Player_SetC4(playerid, amount) {
    PlayerC4[playerid] = amount;
    return 1;
}

stock void:Player_GiveCrack(playerid, amount) {
    PlayerCrack[playerid] += amount;
}

stock Player_GetCrack(playerid) {
    return PlayerCrack[playerid];
}

stock void:Player_GivePicklock(playerid, amount) {
    PlayerPickLock[playerid] += amount;
}

stock Player_GetPicklock(playerid) {
    return PlayerPickLock[playerid];
}

stock void:Player_GiveWallet(playerid, amount) {
    PlayerWallet[playerid] += amount;
}

stock Player_GetWallet(playerid) {
    return PlayerWallet[playerid];
}

stock void:Player_GiveWeed(playerid, amount) {
    PlayerWeed[playerid] += amount;
}

stock Player_GetWeed(playerid) {
    return PlayerWeed[playerid];
}

stock void:Player_GiveCondom(playerid, amount) {
    PlayerCondom[playerid] += amount;
}

stock Player_GetCondom(playerid) {
    return PlayerCondom[playerid];
}

stock void:Player_GiveRope(playerid, amount) {
    PlayerRope[playerid] += amount;
}

stock Player_GetRope(playerid) {
    return PlayerRope[playerid];
}

stock void:Player_GiveScissors(playerid, amount) {
    PlayerScissors[playerid] += amount;
}

stock Player_GetScissors(playerid, amount) {
    return PlayerScissors[playerid];
}

