CMD:rconsetadmin(playerid, params[])
{
    if(IsPlayerAdmin(playerid))
    {
        new target, level;
        if(sscanf(params, "ui", target, level)) return SendSyntaxMsg(playerid, "/setadmin [player] [level]");
        if(target == INVALID_PLAYER_ID) return SendErrorMsg(playerid, "INVALID PLAYER!");
        if(level < 0 || level > MAX_ADMIN_LEVELS)
        {
            SendErrorMsgF(playerid, "Max admin level is %d", MAX_ADMIN_LEVELS);
        }
        Admin_SetPlayerLevel(playerid, level);
        for(new i = 0; i < MAX_PLAYERS; i++)
        {
            if(Admin_GetPlayerLevel(i) > 1)
            {
                SendServerMsgF(playerid, "%p (%d) has been promoted to %s", target, target, Admin_GetRankName(target));
            }
        }
    }
    else return 0;
    return 1;
}