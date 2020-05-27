CMD:bail(playerid) {
    if(PlayerJailed[playerid] == false) {
        return SendErrorMsg(playerid, "You're not jailed!");
    }
    if(timeLeftCounter[playerid] != 0) {
        return SendErrorMsg(playerid, "You've not served your sentence!");
    }
    if(GetPlayerMoney(playerid) < 5000) {
        return SendErrorMsg(playerid, "You don't have enough money to pay 5000");
    }
    Player_UnJail(playerid);
    GivePlayerMoney(playerid, 5000);
    BailBalance[playerid] = 0;
    return 1;
}