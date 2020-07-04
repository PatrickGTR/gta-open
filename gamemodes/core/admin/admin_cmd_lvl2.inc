ACMD:[2]unjail(playerid, params[])
{
    new targetid;
    if(sscanf(params, "u", targetid)) {
        return SendSyntaxMsg(playerid, "/unjail (name/id)");
    }
    if(!IsPlayerConnected(targetid)) {
        return SendErrorMsg(playerid, "The player is not connected!");
    }
    if(!Player_IsInJail(targetid)) {
        return SendErrorMsg(playerid, "The player is not jailed!");
    }
    SendAdminCmdUsage(playerid, "/unjail", params);
    SendMsgAllF(COLOR_MODERATION, "[UNJAIL]: %s %p (%d) has unjailed %p (%d)", Admin_GetRankName(playerid), playerid, playerid, targetid, targetid);
    Player_ReleaseFromJail(targetid);
    return 1;
}