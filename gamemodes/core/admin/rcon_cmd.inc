CMD:rconsetadmin(playerid, params[])
{
    if(IsPlayerAdmin(playerid))
    {
        new target, level;
        if(sscanf(params, "ui", target, level)) return SendSyntaxMsg(playerid, "/rconsetadmin [player] [level]");
        if(target == INVALID_PLAYER_ID) return SendErrorMsg(playerid, "INVALID PLAYER!");
        if(Admin_GetPlayerLevel(target) == level) {
        return SendErrorMsg(playerid, "The player has currently at that admin position");
        }
        if(level < 0 || level > MAX_ADMIN_LEVELS) {
            return SendErrorMsgF(playerid, "Max admin level is %d", MAX_ADMIN_LEVELS);
        }
        Admin_SetPlayerLevel(target, level);
        SendServerMsgF(playerid, "You have promoted %p (%d) to %s", target, target, Admin_GetRankName(target));
    }
    else return 0;
    return 1;
}