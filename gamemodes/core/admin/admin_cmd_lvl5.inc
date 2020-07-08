ACMD:[5]setadmin(playerid, params[])
{
    new target, level;
    if(sscanf(params, "ui", target, level)) return SendSyntaxMsg(playerid, "/setadmin [player] [level]");
    if(target == INVALID_PLAYER_ID) return SendErrorMsg(playerid, "INVALID PLAYER!");
    if(Admin_GetPlayerLevel(target) == 5) {
        return SendErrorMsg(playerid, "You can't demote an developer!");
    }
    if(Admin_GetPlayerLevel(target) == level) {
        return SendErrorMsg(playerid, "The player has currently at that admin position");
    }
    if(level < 0 || level > MAX_ADMIN_LEVELS) {
        return SendErrorMsgF(playerid, "Max admin level is %d", MAX_ADMIN_LEVELS);
    }
    Admin_SetPlayerLevel(target, level);
    SendMsgAllF(COLOR_MODERATION, "%p (%d)'s admin level is set to %s", target, target, Admin_GetRankName(target));
    return 1;
}

ACMD:[5]settester(playerid, params[])
{
    new target, level;
    if(sscanf(params, "ui", target, level)) return SendSyntaxMsg(playerid, "/settester [playerid] [1/0]");
    if(!IsPlayerConnected(target)) {
        return SendErrorMsg(playerid, "Player is not connected!");
    }
    if(level < 0 || level > 1) {
        return SendErrorMsg(playerid, "Use 0 to demote the player use 1 to promote the player");
    }
    if(level == 1 && GetPlayerTester(target)) {
        return SendErrorMsg(playerid, "Player is already a tester");
    }
    if(level == 0 && !GetPlayerTester(target)) {
        return SendErrorMsg(playerid, "Player is not a tester you can't demote him");
    }
    if(level == 1) {
        SetPlayerTester(target, true);
        SendMsgAllF(COLOR_MODERATION, "[BETA INFO]: %p (%d) is now a Beta Tester!", target, target);
    }
    if(level == 0) {
        SetPlayerTester(target, false);
        SendMsgAllF(COLOR_MODERATION, "[BETA INFO]: %p (%d) is demoted from Beta Tester to Normal Player", target, target);
    }
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
    SendMsgAllF(COLOR_MODERATION, "[BANK]: Removed %p (%d)'s Tax Balance.");
    Player_RemoveBankTax(target, Player_GetBankTax(playerid));
    return 1;
}