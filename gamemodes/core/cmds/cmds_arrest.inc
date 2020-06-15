CMD:arrestcw(playerid)
{
    new targetid = Player_GetClosestWanted(playerid);
    if(Player_GetClass(playerid) != TEAM_POLICE) {
        return SendErrorMsg(playerid, "Only cops can use this command!");
    }
    if(!IsPlayerConnected(targetid)) {
        return SendErrorMsg(playerid, "Player is not connected!");
    }
    if(targetid == -1)  {
        return SendErrorMsg(playerid, "There's no warrant near you");
    }
    if(GetPlayerState(targetid) != PLAYER_STATE_ONFOOT) {
        SendServerMsgF(playerid, "You have asked %p (%d) to pull over!", targetid, targetid);
        SendServerMsgF(targetid, "Officer %p (%d) has asked you to pull over!", playerid, playerid);
        return 0;
    }
    if(Player_IsCuffed(targetid) == false) {
        return SendErrorMsg(playerid, "You need to cuff the player first!");
    }

    ApplyAnimation(targetid, "SHOP", "SHP_Rob_HandsUp", 4.1, 0, 1, 1, 1, 3000, 1);
    ApplyAnimation(playerid, "PED", "ARRESTgun", 4.1, 0, 1, 1, 1, 3000, 1);

    SendServerMsgF(playerid, "You have arrested %p (%d)", targetid, targetid);
    SendServerMsgF(targetid, "You have been arrested by %p (%d)", playerid, playerid);

    Player_SendToJail(targetid, 300, true);
    return 1;
}

CMD:arcw(playerid)
{
    return cmd_arrestcw(playerid);
}

CMD:arrest(playerid, params[])
{
    new targetid;
    if(sscanf(params, "u", targetid)) {
        return SendSyntaxMsg(playerid, "/arrest (name/id)");
    }
    if(Player_GetClass(playerid) != TEAM_POLICE) {
        return SendErrorMsg(playerid, "Only cops can use this command!");
    }
    if(!IsPlayerConnected(targetid)) {
        return SendErrorMsg(playerid, "Player is not connected!");
    }
    if(targetid == playerid) {
        return SendErrorMsg(playerid, "You can't arrest yourself!");
    }
    if(Player_GetWantedLevel(targetid) <= 3) {
        return SendErrorMsg(playerid, "Player is not wanted!");
    }
    if(GetPlayerState(targetid) != PLAYER_STATE_ONFOOT) {
        SendServerMsgF(playerid, "You have asked %p (%d) to pull over!", targetid, targetid);
        SendServerMsgF(targetid, "Officer %p (%d) has asked you to pull over!", playerid, playerid);
        return 0;
    }
    if(Player_IsCuffed(targetid) == false) {
        return SendErrorMsg(playerid, "You need to cuff the player first!");
    }

    ApplyAnimation(targetid, "SHOP", "SHP_Rob_HandsUp", 4.1, 0, 1, 1, 1, 3000, 1);
    ApplyAnimation(playerid, "PED", "ARRESTgun", 4.1, 0, 1, 1, 1, 3000, 1);

    SendServerMsgF(playerid, "You have arrested %p (%d)", targetid, targetid);
    SendServerMsgF(targetid, "You have been arrested by %p (%d)", playerid, playerid);

    Player_SendToJail(targetid, 300, true);
    return 1;
}

CMD:ar(playerid, params[])
{
    return cmd_arrest(playerid, params);
}