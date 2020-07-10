ACMD:[2]jail(playerid, params[])
{
    new target, seconds, reason[128];
    if(sscanf(params, "uis[128]", target, seconds, reason)) return SendSyntaxMsg(playerid, "/jail (name/id) (seconds) (reason)");
    Player_SendToJail(target, seconds, true);
    SendMsgAllF(COLOR_MODERATION, "[ADMIN JAIL]: %p (%d) has been jailed for %d seconds", target, target, seconds);
    SendMsgAllF(COLOR_MODERATION, "Reason: %s", reason);
    SendMsgF(target, COLOR_MODERATION, "[ADMIN JAIL]: You have been jailed for %d Seconds", seconds);
    SendAdminCmdUsage(playerid, "/jail", params);
    return 1;
}

ACMD:[2]unjail(playerid, params[])
{
    new targetid;
    if(sscanf(params, "u", targetid)) {
        return SendSyntaxMsg(playerid, "/unjail (name/id)");
    }
    if(!IsPlayerConnected(targetid)) {
        return SendErrorMsg(playerid, "The player is not connected!");
    }
    if(!Player_InJail(targetid)) {
        return SendErrorMsg(playerid, "The player is not jailed!");
    }
    SendAdminCmdUsage(playerid, "/unjail", params);
    SendMsgAllF(COLOR_MODERATION, "[UNJAIL]: %s %p (%d) has unjailed %p (%d)", Admin_GetRankName(playerid), playerid, playerid, targetid, targetid);
    Player_ReleaseFromJail(targetid);
    return 1;
}