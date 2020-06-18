ACMD:[3]ban(playerid, params[])
{
    if (isnull(params) || isnumeric(params))  {
        SendClientMessage(playerid, COLOR_YELLOW, "/ban day | month | year");
        return 1;
    }

    new
        targetid = INVALID_PLAYER_ID,
        reason[MAX_BAN_REASON] = '\0',
        duration = -1;

    if (!strcmp(params, "day", true, 4)) {
        if (sscanf(params, "{s[5]}riS(No Reason)[32]", targetid, duration, reason)) {
            SendSyntaxMsg(playerid, "/ban day <playerid> <duration> <reason>");
            return 1;
        }
        if (!(IsPlayerConnected(targetid))) {
            SendSyntaxMsg(playerid, "The player you are trying to ban is not connected.");
            return 1;
        }
        if (strlen(reason) > MAX_BAN_REASON) {
            SendSyntaxMsg(playerid, "The lenght of the reason is too long, maximum characters is 32");
            return 1;
        }
        Ban_AddUser(targetid, playerid, reason, 0, duration);
    }
    if (!strcmp(params, "month", true, 5)) {
        if (sscanf(params, "{s[6]}riS(No Reason)[50]", targetid, duration, reason))
        {
            SendSyntaxMsg(playerid, "/ban month <playerid> <duration> <reason>");
            return 1;
        }
        if (!(IsPlayerConnected(targetid)))
        {
            SendSyntaxMsg(playerid, "The player you are trying to ban is not connected.");
            return 1;
        }
        if (strlen(reason) > MAX_BAN_REASON)
        {
            SendSyntaxMsg(playerid, "The lenght of the reason is too long, maximum characters is 32");
            return 1;
        }

        Ban_AddUser(targetid, playerid, reason, 1, duration);
    }
    if (!strcmp(params, "year", true, 4))  {
        if (sscanf(params, "{s[5]}riS(No Reason)[50]", targetid, duration, reason)) {
            SendSyntaxMsg(playerid, "/ban year <playerid> <duration> <reason>");
            return 1;
        }
        if (!(IsPlayerConnected(targetid))) {
            SendSyntaxMsg(playerid, "The player you are trying to ban is not connected.");
            return 1;
        }
        if (strlen(reason) > MAX_BAN_REASON) {
            SendSyntaxMsg(playerid, "The lenght of the reason is too long, maximum characters is 32");
            return 1;
        }
        Ban_AddUser(targetid, playerid, reason, 2, duration);
    }

    SendMsgF(playerid, COLOR_RED, "[BANNED]: "C_WHITE"You have been banned by admin "C_GREY"%p "C_WHITE"for "C_GREY"%s", playerid, reason);
    Kick(targetid);
    return 1;
}

ACMD:[3]unban(playerid, params[])
{
    if (isnull(params) || strval(params)) {
        SendSyntaxMsg(playerid, "/unban <playername>");
        return 1;
    }
    if (strlen(params) > MAX_PLAYER_NAME) {
        SendErrorMsg(playerid, "MAX_PLAYER_NAME = 24, type the name again!");
        return 1;
    }

    Ban_RemoveUser(params, playerid);
    return 1;
}