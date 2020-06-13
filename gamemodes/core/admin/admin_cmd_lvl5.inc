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
    SendServerMsgF(playerid, "%p (%d) has been promoted to %s", target, target, Admin_GetRankName(target));
    return 1;
}