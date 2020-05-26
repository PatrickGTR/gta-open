CMD:arrestcw(playerid)
{
    new ClosesWar = Player_GetClosestWanted(playerid);
    if(Player_GetClass(playerid) != TEAM_POLICE) {
        return SendErrorMsg(playerid, "Only cops can use this command!");
    }
    if(!IsPlayerConnected(ClosesWar)) {
        return SendErrorMsg(playerid, "Player is not connected!");
    }
    if(GetPlayerState(ClosesWar) != PLAYER_STATE_ONFOOT) {
        SendServerMsgF(playerid, "You have asked %p (%d) to pull over!", ClosesWar, ClosesWar);
        SendServerMsgF(ClosesWar, "Officer %p (%d) has asked you to pull over!", playerid, playerid);
        return 0;
    }
    if(PlayerCuffed[ClosesWar] == false) {
        return SendErrorMsg(playerid, "You need to cuff the player first!");
    }
    if(PlayerJailed[ClosesWar] == true) {
        return SendErrorMsg(playerid, "Player is jailed now!");
    }
    SetPlayerSpecialAction(ClosesWar, SPECIAL_ACTION_NONE);
    ApplyAnimation(ClosesWar, "SHOP", "SHP_Rob_HandsUp", 4.1, 0, 1, 1, 1, 3000, 1);
    ApplyAnimation(playerid, "PED", "ARRESTgun", 4.1, 0, 1, 1, 1, 3000, 1);
    SendServerMsgF(playerid, "You have arrested %p (%d)", ClosesWar, ClosesWar);
    SendServerMsgF(ClosesWar, "You have been arrested by %p (%d)", playerid, playerid);
    Player_Jail(ClosesWar);
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
    if(GetPlayerState(targetid) != PLAYER_STATE_ONFOOT) {
        SendServerMsgF(playerid, "You have asked %p (%d) to pull over!", targetid, targetid);
        SendServerMsgF(targetid, "Officer %p (%d) has asked you to pull over!", playerid, playerid);
        return 0;
    }
    if(PlayerCuffed[targetid] == false) {
        return SendErrorMsg(playerid, "You need to cuff the player first!");
    }
    if(PlayerJailed[targetid] == true) {
        return SendErrorMsg(playerid, "Player is jailed now!");
    }
    SetPlayerSpecialAction(targetid, SPECIAL_ACTION_NONE);
    ApplyAnimation(targetid, "SHOP", "SHP_Rob_HandsUp", 4.1, 0, 1, 1, 1, 3000, 1);
    ApplyAnimation(playerid, "PED", "ARRESTgun", 4.1, 0, 1, 1, 1, 3000, 1);
    Player_Jail(targetid);
    return 1;
}

CMD:ar(playerid, params[])
{
    return cmd_arrest(playerid, params);
}