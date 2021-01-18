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

ACMD:[5]settester(playerid, params[])
{
    new
        targetid,
        bool:testerState;
    if(sscanf(params, "ul", targetid, testerState)) {
        return SendSyntaxMsg(playerid, "/settester (name/id) (0/1)");
    }

    if(!IsPlayerConnected(targetid)) {
        return SendErrorMsg(playerid, "Player is not connected!");
    }

    if(testerState && GetPlayerTester(targetid)) {
        return SendErrorMsg(playerid, "Player is already a tester");
    }
    if(!testerState && !GetPlayerTester(targetid)) {
        return SendErrorMsg(playerid, "Player is not a tester you can't demote him");
    }

    SetPlayerTester(targetid, testerState);
    SendMsgAllF(COLOR_MODERATION, "(BETA TESTER) "C_GREY"%p(%d) "C_WHITE"is %s a "C_GREY"Beta Tester", targetid, targetid, (testerState) ? ("now") : ("no longer"));
    return 1;
}

ACMD:[5]setplayerdept(playerid, params[])
{
    new target, value;
    if(sscanf(params, "ui", target)) return SendSyntaxMsg(playerid, "/setplayerdept (name/id) (bank dept.)");
    if(!IsPlayerConnected(target)) {
        return SendErrorMsg(playerid, "Player is not connected");
    }
    SendMsgAllF(COLOR_MODERATION, "[BANK DEPT.]: An Administrator sets %p (%d)'s bank dept. to %d", target, target, value);
    Player_AddBankDept(target, value, true);
    SendMsgAllF(COLOR_MODERATION, "[BANK]: %p (%d)'s Total Bank Dept. is %d", target, target, Player_GetBankDept(playerid));
    return 1;
}

ACMD:[5]bankrupt(playerid, params[])
{
    new target;
    if(sscanf(params, "u", target)) return SendSyntaxMsg(playerid, "/bankrupt (name/id)");
    if(!IsPlayerConnected(target)) {
        return SendErrorMsg(playerid, "Player is not connected");
    }
    SendMsgAllF(COLOR_MODERATION, "[BANKRUPT]: An Administrator bankrupted %p (%d)", target, target);
    SendMsgAllF(COLOR_MODERATION, "[BANK]: Removed %d from %p (%d)'s account", Player_GetBankMoney(playerid), target, target);
    Player_RemoveBankMoney(target, Player_GetBankMoney(target));
    SendMsgAllF(COLOR_MODERATION, "[BANK]: Removed %p (%d)'s Tax Balance.", target, target);
    Player_RemoveBankTax(target, Player_GetBankTax(playerid));
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
