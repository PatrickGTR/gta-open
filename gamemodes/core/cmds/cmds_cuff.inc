CMD:cuffcw(playerid)
{
    new
        targetid = Player_GetClosestWanted(playerid),
        Float:x,
        Float:y,
        Float:z;
    GetPlayerPos(playerid, x, y, z);
    if(Player_GetClass(playerid) != TEAM_POLICE) {
        return SendErrorMsg(playerid, "Only cops can use this command!");
    }
    if(targetid == -1)  {
        return SendErrorMsg(playerid, "There's no warrant near you");
    }
    if(!IsPlayerInRangeOfPoint(targetid, 5.0, x, y, z)) {
        return SendErrorMsg(playerid, "There's no warrant near you");
    }
    if(GetPlayerState(targetid) != PLAYER_STATE_ONFOOT) {
        SendServerMsgF(playerid, "You have asked %p (%d) to pull over!", targetid, targetid);
        SendServerMsgF(targetid, "%p (%d) has asked you to pull over", playerid, playerid);
        return 0;
    }
    if(Player_IsCuffed(targetid)) {
        return SendErrorMsg(playerid, "The player is already cuffed");
    }
    SendServerMsgF(targetid, "You have been cuffed by officer %p (%d)", playerid, playerid);
    SendServerMsgF(playerid, "You're now cuffing %p (%d)", targetid, targetid);

    Player_Cuff(targetid, true);
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
    if(targetid == playerid) {
        return SendErrorMsg(playerid, "You can't cuff yourself");
    }
    if(Player_GetWantedLevel(targetid) <= 3) {
        return SendErrorMsg(playerid, "Player is not wanted!");
    }
    if(!IsPlayerInRangeOfPoint(targetid, 5.0, x, y, z)) {
        return SendErrorMsgF(playerid, "%p (%d) is not close to you", targetid, targetid);
    }
    if(GetPlayerState(targetid) != PLAYER_STATE_ONFOOT) {
        SendServerMsgF(playerid, "You have asked %p (%d) to pull over!", targetid, targetid);
        SendServerMsgF(targetid, "%p (%d) has asked you to pull over", playerid, playerid);
        return 0;
    }
    if(Player_IsCuffed(targetid)) {
        return SendErrorMsg(playerid, "The player is already cuffed");
    }
    SendServerMsgF(targetid, "You have been cuffed by officer %p (%d)", playerid, playerid);
    SendServerMsgF(playerid, "You're now cuffing %p (%d)", targetid, targetid);


    Player_Cuff(targetid, true);
    return 1;
}

