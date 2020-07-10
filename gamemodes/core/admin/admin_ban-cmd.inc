ACMD:[2]tempban(playerid, params[])
{
    if (isnull(params) || isnumeric(params))  {
        return SendSyntaxMsg(playerid, "/tempban <options: d(ay), m(onth), y(ear)>");
    }

    new
        targetid = INVALID_PLAYER_ID,
        reason[MAX_BAN_REASON] = '\0',
        duration = -1,
        bool:success = false,
        interval = -1;

    if (!strcmp(params, "d", true, 1)) {
        if (sscanf(params, "{s[2]}riS(Not specified)["#MAX_BAN_REASON"]", targetid, duration, reason)) {
            return SendSyntaxMsg(playerid, "/tempban d <playerid> <duration> <reason>");
        }
        if (!IsPlayerConnected(targetid)) {
            return SendErrorMsg(playerid, "The player you are trying to ban is not connected.");
        }
        if (strlen(reason) > MAX_BAN_REASON) {
            return SendErrorMsg(playerid, "The lenght of the reason is too long, maximum characters is 32");
        }
        interval = 0;
    }
    if (!strcmp(params, "m", true, 1)) {
        if (sscanf(params, "{s[2]}riS(Not specified)["#MAX_BAN_REASON"]", targetid, duration, reason)) {
            return SendSyntaxMsg(playerid, "/tempban m <playerid> <duration> <reason>");
        }
        if (!IsPlayerConnected(targetid)) {
            return SendErrorMsg(playerid, "The player you are trying to ban is not connected.");
        }
        if (strlen(reason) > MAX_BAN_REASON) {
            return SendErrorMsg(playerid, "The lenght of the reason is too long, maximum characters is 32");
        }

        interval = 1;
    }
    if (!strcmp(params, "y", true, 1))  {
        if (sscanf(params, "{s[2]}riS(Not specified)["#MAX_BAN_REASON"]", targetid, duration, reason)) {
            return SendSyntaxMsg(playerid, "/tempban y <playerid> <duration> <reason>");
        }
        if (!IsPlayerConnected(targetid)) {
            return SendErrorMsg(playerid, "The player you are trying to ban is not connected.");
        }
        if (strlen(reason) > MAX_BAN_REASON) {
            return SendErrorMsg(playerid, "The lenght of the reason is too long, maximum characters is 32");
        }
        interval = 2;
    }

    if(interval != -1) {
        success = !!Ban_AddUser(targetid, playerid, reason, interval, duration);
    }

    if(success) {
        SendMsgF(playerid, COLOR_MODERATION, "[ACCOUNT DISABLE]: You have Disabled "C_GREY"%p's account "C_WHITE"for "C_GREY"%s", targetid, reason);
        SendMsgAllF(COLOR_MODERATION, "[ACCOUNT DISABLED]: %p (%d) has been banned for %s", targetid, targetid, reason);
        SendMsgF(targetid, COLOR_MODERATION, "[ACCOUNT DISABLED]: You have been banned by an Admin for %s", reason);
        defer KickTimer(targetid);
    }
    return 1;
}

ACMD:[3]unban(playerid, params[])
{
    if (isnull(params) || strval(params)) {
        return SendSyntaxMsg(playerid, "/unban <playername>");
    }
    if (strlen(params) > MAX_PLAYER_NAME) {
        return SendErrorMsg(playerid, "MAX_PLAYER_NAME = 24, type the name again!");
    }

    Ban_RemoveUser(params, playerid);
    return 1;
}