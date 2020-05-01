ACMD:[5]setadmin(playerid, params[])
{
    new target, level, string[128];
    new pname[MAX_PLAYER_NAME];
    GetPlayerName(playerid, pname, sizeof(pname));
    if(sscanf(params, "ui", target, level)) return SendClientMessage(playerid, -1, "USAGE: /setadmin [player] [level]");
    if(target == INVALID_PLAYER_ID) return SendClientMessage(playerid, -1, "ERROR: INVALID PLAYER!");
    if(level < 0 || level > MAX_ADMIN_LEVELS)
    {
        format(string, sizeof(string), "Max admin level is %d", MAX_ADMIN_LEVELS);
        SendClientMessage(playerid, -1, string);
    }
    Admin_SetPlayerLevel(playerid, level);
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        if(Admin_GetPlayerLevel(i) >= 1)
        {
            format(string, sizeof(string), "%s (%d) has been promoted to %s admin", pname, target, Admin_GetRankName(target));
            SendClientMessage(playerid, -1, string);
        }
    }
    return 1;
}