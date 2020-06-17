ACMD:[5]setadmin(playerid, params[])
{
    new target, level;
    if(sscanf(params, "ui", target, level)) return SendSyntaxMsg(playerid, "/setadmin [player] [level]");
    if(target == INVALID_PLAYER_ID) return SendErrorMsg(playerid, "INVALID PLAYER!");
    if(Admin_GetPlayerLevel(target) == 5) {
        return SendErrorMsg(playerid, "You can't demote an developer!");
    }
    if(Admin_GetPlayerLevel(target) == level) {
        return SendErrorMsg(playerid, "The player has currently at that admin position");
    }
    if(level < 0 || level > MAX_ADMIN_LEVELS) {
        return SendErrorMsgF(playerid, "Max admin level is %d", MAX_ADMIN_LEVELS);
    }
    Admin_SetPlayerLevel(target, level);
    foreach(new i : Player)
    {
        if(i != INVALID_PLAYER_ID)
        {
            SendServerMsgF(i, "%p (%d)'s admin level is set to %s", target, target, Admin_GetRankName(target));
        }
    }
    return 1;
}

ACMD:[5]settester(playerid, params[])
{
    new target, level;
    if(sscanf(params, "ui", target, level)) return SendSyntaxMsg(playerid, "/settester [playerid] [1/0]");
    if(!IsPlayerConnected(target)) {
        return SendErrorMsg(playerid, "Player is not connected!");
    }
    if(level < 0 || level > 1) {
        return SendErrorMsg(playerid, "Use 0 to demote the player use 1 to promote the player");
    }
    if(level == 1 && GetPlayerTester(target)) {
        return SendErrorMsg(playerid, "Player is already a tester");
    }
    if(level == 0 && !GetPlayerTester(target)) {
        return SendErrorMsg(playerid, "Player is not a tester you can't demote him");
    }
    if(level == 1) {
        SetPlayerTester(target, true);
        foreach(new i : Player) {
            if(i != INVALID_PLAYER_ID) 
            {
                SendServerMsgF(i, "%p (%d) is now a Beta Tester!", target, target);
            }
        }
    }
    if(level == 0) {
        SetPlayerTester(target, false);
        foreach(new i : Player) {
            if(i != INVALID_PLAYER_ID) 
            {
                SendServerMsgF(i, "%p (%d) is demoted from Beta Tester to Normal Player", target, target);
            }
        }
    }
    return 1;
}