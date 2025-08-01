ACMD:[2]tempban(playerid, params[])
{
    if (isnull(params) || IsNumeric(params))  {
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
        if (targetid == playerid) {
            return SendErrorMsg(playerid, "You can't ban yourself");
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
        if (targetid == playerid) {
            return SendErrorMsg(playerid, "You can't ban yourself");
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
        if (targetid == playerid) {
            return SendErrorMsg(playerid, "You can't ban yourself");
        }
        if (strlen(reason) > MAX_BAN_REASON) {
            return SendErrorMsg(playerid, "The lenght of the reason is too long, maximum characters is 32");
        }
        interval = 2;
    }

    if(interval != -1) {
        success = bool:Ban_AddUser(targetid, playerid, reason, interval, duration);
    }

    if(success) {
        SendMsgF(playerid, COLOR_MODERATION, "[ADMIN]: You have Disabled %p's account for %s", targetid, reason);
        SendMsgF(targetid, COLOR_MODERATION, "[ADMIN]: You have been banned by an Admin for %s", reason);

        SendMsgAllF(COLOR_MODERATION, "[ADMIN]: %p(%d) has been banned for %s", targetid, targetid, reason);
        Kick(targetid);
    }
    return 1;
}

ACMD:[2]offban(playerid, params[])
{
    if (isnull(params) || IsNumeric(params))  {
        return SendSyntaxMsg(playerid, "/offban <options: d(ay), m(onth), y(ear)>");
    }
    new
        targetname[MAX_PLAYER_NAME],
        reason[MAX_BAN_REASON] = '\0',
        duration = -1,
        bool:success = false,
        interval = -1;
    if (!strcmp(params, "d", true, 1)) {
        if (sscanf(params, "{s[2]}s[24]iS(Not specified)["#MAX_BAN_REASON"]", targetname, duration, reason)) {
            return SendSyntaxMsg(playerid, "/offban d <playername> <duration> <reason>");
        }
        if (strlen(reason) > MAX_BAN_REASON) {
            return SendErrorMsg(playerid, "The lenght of the reason is too long, maximum characters is 32");
        }
        interval = 0;
    }
    if (!strcmp(params, "m", true, 1)) {
        if (sscanf(params, "{s[2]}s[24]iS(Not specified)["#MAX_BAN_REASON"]", targetname, duration, reason)) {
            return SendSyntaxMsg(playerid, "/offban m <playername> <duration> <reason>");
        }
        if (strlen(reason) > MAX_BAN_REASON) {
            return SendErrorMsg(playerid, "The lenght of the reason is too long, maximum characters is 32");
        }

        interval = 1;
    }
    if (!strcmp(params, "y", true, 1))  {
        if (sscanf(params, "{s[2]}s[24]iS(Not specified)["#MAX_BAN_REASON"]", targetname, duration, reason)) {
            return SendSyntaxMsg(playerid, "/offban y <playername> <duration> <reason>");
        }
        if (strlen(reason) > MAX_BAN_REASON) {
            return SendErrorMsg(playerid, "The lenght of the reason is too long, maximum characters is 32");
        }
        interval = 2;
    }

    if(interval != -1) {
        success = !!OffBan_AddUser(targetname, playerid, reason, interval, duration);
    }

    if(success) {
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