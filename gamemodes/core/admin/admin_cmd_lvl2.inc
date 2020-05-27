ACMD:[2]unjail(playerid, params[])
{
    new targetid;
    if(sscanf(params, "u", targetid)) {
        return SendSyntaxMsg(playerid, "/unjail (name/id)");
    }
    if(!IsPlayerConnected(targetid)) {
        return SendErrorMsg(playerid, "The player is not connected!");
    }
    if(!Player_IsJailed(targetid)) {
        return SendErrorMsg(playerid, "The player is not jailed!");
    }
    SendMsgAllF(COLOR_PURPLE, "[UNJAIL]: %s %p (%d) has unjailed %p (%d)", Admin_GetRankName(playerid), playerid, playerid, targetid, targetid);
    Player_UnJail(targetid);
    Player_SetJail(targetid, false);
    return 1;
}