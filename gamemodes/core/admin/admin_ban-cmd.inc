ACMD:[3]ban(playerid, params[])
{
    if (isnull(params) || isnumeric(params))  {
        return SendSyntaxMsg(playerid, "/ban <options: d(ay), m(onth), y(ear)>");
    }

    new
        targetid = INVALID_PLAYER_ID,
        reason[MAX_BAN_REASON] = '\0',
        duration = -1,
        bool:success = false,
        interval = -1;

    if (!strcmp(params, "d", true, 1)) {
        if (sscanf(params, "{s[2]}riS(Not specified)["#MAX_BAN_REASON"]", targetid, duration, reason)) {
            return SendSyntaxMsg(playerid, "/ban d <playerid> <duration> <reason>");
        }
        if (!IsPlayerConnected(targetid)) {
            return SendSyntaxMsg(playerid, "The player you are trying to ban is not connected.");
        }
        if (strlen(reason) > MAX_BAN_REASON) {
            return SendSyntaxMsg(playerid, "The lenght of the reason is too long, maximum characters is 32");
        }
        interval = 0;

    }
    if (!strcmp(params, "m", true, 1)) {
        if (sscanf(params, "{s[2]}riS(Not specified)["#MAX_BAN_REASON"]", targetid, duration, reason)) {
            return SendSyntaxMsg(playerid, "/ban m <playerid> <duration> <reason>");
        }
        if (!IsPlayerConnected(targetid)) {
            return SendSyntaxMsg(playerid, "The player you are trying to ban is not connected.");
        }
        if (strlen(reason) > MAX_BAN_REASON) {
            return SendSyntaxMsg(playerid, "The lenght of the reason is too long, maximum characters is 32");
        }

        interval = 1;
    }
    if (!strcmp(params, "y", true, 1))  {
        if (sscanf(params, "{s[2]}riS(Not specified)["#MAX_BAN_REASON"]", targetid, duration, reason)) {
            return SendSyntaxMsg(playerid, "/ban y <playerid> <duration> <reason>");
        }
        if (!IsPlayerConnected(targetid)) {
            return SendSyntaxMsg(playerid, "The player you are trying to ban is not connected.");
        }
        if (strlen(reason) > MAX_BAN_REASON) {
            return SendSyntaxMsg(playerid, "The lenght of the reason is too long, maximum characters is 32");
        }
        interval = 2;
    }

    if(interval != -1) {
        success = !!Ban_AddUser(targetid, playerid, reason, interval, duration);
    }

    if(success) {
        SendServerMsgF(playerid, "You have banned "C_GREY"%p "C_WHITE"for "C_GREY"%s", targetid, reason);
        SendMsgF(targetid, COLOR_RED, "[BANNED]: "C_WHITE"You have been banned by admin "C_GREY"%p "C_WHITE"for "C_GREY"%s", playerid, reason);
        Kick(targetid);
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