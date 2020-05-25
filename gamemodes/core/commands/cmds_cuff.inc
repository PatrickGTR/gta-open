CMD:cuffcw(playerid)
{
    new ClosesWar = Player_GetClosestWanted(playerid);
    new
        Float:x,
        Float:y,
        Float:z;
    GetPlayerPos(playerid, x, y, z);
    if(Player_GetClass(playerid) != TEAM_POLICE) {
        return SendErrorMsg(playerid, "Only cops can use this command!");
    }
    if(!IsPlayerConnected(ClosesWar)) {
        return SendErrorMsg(playerid, "Player is not connected!");
    }
    if(!IsPlayerInRangeOfPoint(ClosesWar, 5.0, x, y, z)) {
        return SendErrorMsg(playerid, "There's no warrant near you");
    }
    if(PlayerCuffed[ClosesWar] == true) {
        return SendErrorMsg(playerid, "The player is already cuffed");
    }
    SendServerMsgF(ClosesWar, "You have been cuffed by officer %p (%d)", playerid, playerid);
    SendServerMsgF(playerid, "You're now cuffing %p (%d)", ClosesWar, ClosesWar);
    SetPlayerAttachedObject(ClosesWar, 0, 19418, 6, -0.011000, 0.028000, -0.022000, -15.600012, -33.699977,-81.700035, 0.891999, 1.000000, 1.168000);
    SetPlayerSpecialAction(ClosesWar, SPECIAL_ACTION_CUFFED);
    PlayerCuffed[ClosesWar] = true;
    return 1;
}

CMD:cuff(playerid, params[])
{
    new
        Float:x,
        Float:y,
        Float:z,
        targetid
    ;
    if(sscanf(params, "u", targetid)) {
        return SendSyntaxMsg(playerid, "/cuff (name/id)");
    }
    GetPlayerPos(playerid, x, y, z);
    if(Player_GetClass(playerid) != TEAM_POLICE) {
        return SendErrorMsg(playerid, "Only cops can use this command!");
    }
    if(!IsPlayerConnected(targetid)) {
        return SendErrorMsg(playerid, "Player is not connected!");
    }
    if(!IsPlayerInRangeOfPoint(targetid, 5.0, x, y, z)) {
        return SendErrorMsg(playerid, "There's no warrant near you");
    }
    if(PlayerCuffed[targetid] == true) {
        return SendErrorMsg(playerid, "The player is already cuffed");
    }
    SendServerMsgF(targetid, "You have been cuffed by officer %p (%d)", playerid, playerid);
    SendServerMsgF(playerid, "You're now cuffing %p (%d)", targetid, targetid);
    SetPlayerAttachedObject(targetid, 0, 19418, 6, -0.011000, 0.028000, -0.022000, -15.600012, -33.699977,-81.700035, 0.891999, 1.000000, 1.168000);
    SetPlayerSpecialAction(targetid, SPECIAL_ACTION_CUFFED);
    PlayerCuffed[targetid] = true;
    return 1;
}