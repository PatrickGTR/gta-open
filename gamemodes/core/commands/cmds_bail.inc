CMD:bail(playerid) {
    if(PlayerJailed[playerid] == false) {
        return SendErrorMsg(playerid, "You're not jailed!");
    }
    if(timeLeftCounter[playerid] != 0) {
        return SendErrorMsg(playerid, "You've not served your sentence!");
    }
    if(GetPlayerMoney(playerid) < Player_GetBailAmount(playerid)) {
        return SendErrorMsgF(playerid, "You don't have "C_GREEN"$%i "C_WHITE"to pay for your bail.", Player_GetBailAmount(playerid));
    }
    Player_UnJail(playerid);
    GivePlayerMoney(playerid, Player_GetBailAmount(playerid));
    Player_SetBailAmount(playerid, 0);
    return 1;
}