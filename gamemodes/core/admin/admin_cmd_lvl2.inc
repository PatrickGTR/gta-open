ACMD:[2]jail(playerid, params[])
{
    new
        targetid,
        seconds,
        reason[32];

    if(sscanf(params, "uiS[32](No Reason)", targetid, seconds, reason)) {
        return SendSyntaxMsg(playerid, "/jail (name/id) (seconds) (reason)");
    }

    if(!IsPlayerConnected(targetid)) {
        return SendErrorMsg(playerid, "The player is not connected!");
    }


    SendMsgAllF(COLOR_MODERATION, "[ADMIN JAIL]: %p (%d) has been jailed for %d seconds", targetid, targetid, seconds);
    SendMsgAllF(COLOR_MODERATION, "[ADMIN JAIL]: reason: %s", reason);

    SendMsgF(targetid, COLOR_MODERATION, "[ADMIN JAIL]: You have been jailed for %d Seconds", seconds);
    SendMsgF(targetid, COLOR_MODERATION, "[ADMIN JAIL]: reason: %s", reason);

    Player_SendToJail(targetid, seconds, true);
    return 1;
}

ACMD:[2]unjail(playerid, params[])
{
    new
        targetid;

    if(sscanf(params, "u", targetid)) {
        return SendSyntaxMsg(playerid, "/unjail (name/id)");
    }

    if(!IsPlayerConnected(targetid)) {
        return SendErrorMsg(playerid, "The player is not connected!");
    }

    if(!Player_IsInJail(targetid)) {
        return SendErrorMsg(playerid, "The player is not jailed!");
    }

    SendMsgAllF(COLOR_MODERATION, "[UNJAIL]: %s %p (%d) has unjailed %p (%d)", Admin_GetRankName(playerid), playerid, playerid, targetid, targetid);
    Player_ReleaseFromJail(targetid);
    return 1;
}