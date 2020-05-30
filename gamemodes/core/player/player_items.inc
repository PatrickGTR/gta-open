static 
    PlayerCondom[MAX_PLAYERS];


Player_GetCondom(playerid) {
    return PlayerCondom[playerid];
}

Player_SetCondom(playerid, amount) {
    PlayerCondom[playerid] = amount;
    return 1;
}