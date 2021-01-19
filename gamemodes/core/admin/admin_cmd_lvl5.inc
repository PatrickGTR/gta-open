ACMD:[5]setadmin(playerid, params[])
{
    new
        targetid,
        level;

    if(sscanf(params, "ui", targetid, level)) {
        return SendSyntaxMsg(playerid, "/setadmin [player] [level]");
    }

    if(IsPlayerConnected(targetid)) {
        return SendErrorMsg(playerid, "INVALID PLAYER!");
    }

    if(Admin_GetPlayerLevel(targetid) == 5) {
        return SendErrorMsg(playerid, "You can't demote a developer!");
    }

    if(Admin_GetPlayerLevel(targetid) == level) {
        return SendErrorMsg(playerid, "The player has currently at that admin position");
    }

    if(!IS_IN_RANGE(level, 0, MAX_ADMIN_LEVELS)) {
        return SendErrorMsgF(playerid, "The admin levels are 0 to %i", MAX_ADMIN_LEVELS);
    }

    Admin_SetPlayerLevel(targetid, level);
    SendMsgAllF(COLOR_MODERATION, "%p(%d)'s admin level is set to %s", targetid, targetid, Admin_GetRankName(targetid));
    return 1;
}

ACMD:[5]skick(playerid, params[])
{
    new target;
    if(sscanf(params, "u", target)) return SendSyntaxMsg(playerid, "/skick (name/id)");
    if(!IsPlayerConnected(target)) {
        return SendErrorMsg(playerid, "Player is not connected");
    }
    Kick(target);
    return 1;
}
