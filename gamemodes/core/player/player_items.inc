static 
    PlayerCondom[MAX_PLAYERS],
    PlayerC4[MAX_PLAYERS];

stock Player_GetC4(playerid) {
    return PlayerC4[playerid];
}

stock Player_SetC4(playerid, amount) {
    PlayerC4[playerid] = amount;
    return 1;
}

stock Player_GetCondom(playerid) {
    return PlayerCondom[playerid];
}

stock Player_SetCondom(playerid, amount) {
    PlayerCondom[playerid] = amount;
    return 1;
}