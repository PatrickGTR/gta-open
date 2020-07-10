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

ACMD:[5]givescore(playerid, params[])
{
    new target, score;
    if(sscanf(params, "ui", target, score)) return SendSyntaxMsg(playerid, "/givescore (name/id) (score)");
    Player_GiveScore(target, score, true);
    return 1;
}

ACMD:[5]removescore(playerid, params[])
{
    new target, score;
    if(sscanf(params, "ui", target, score)) return SendSyntaxMsg(playerid, "/removescore (name/id) (score)");
    Player_RemoveScore(target, score);
    return 1;
}

ACMD:[5]setarmy(playerid, params[])
{
    new target, level, string[256];
    if(sscanf(params, "ui", target, level)) return SendSyntaxMsg(playerid, "/givearmy (name/id) (1/0)");
    if(!IsPlayerConnected(target)) {
        return SendErrorMsg(playerid, "Player is not connected");
    }
    if(IsPlayerBlacklisted(target)) {
        return SendErrorMsg(playerid, "Player is Blacklisted from army. Do /unblacklist (name/id)");
    }
    if(level < 0 || level > 1) {
        return SendErrorMsg(playerid, "1 = player can select army 0 = player can't select");
    } 
    if(level == 0) {
        static const deleteQuery[] = "\
        UPDATE \
            armys \
        SET \
            IsArmy = %i \
        WHERE \
            u_id = %i \
        ";
        mysql_format(MySQL_GetHandle(), string, sizeof(string), deleteQuery, level, Player_GetAccountID(target));
        mysql_tquery(MySQL_GetHandle(), string);
        Player_SetArmy(playerid, false);
        SendMsgAllF(COLOR_MODERATION, "[ARMY]: %p (%d) is removed from the army. By the Owner's decision");
    }
    if(level == 1) {
        static const insertQuery[] = "\
        UPDATE \
            armys \
        SET \
            IsArmy = %i \
        WHERE \
            u_id = %i \
        ";
        mysql_format(MySQL_GetHandle(), string, sizeof(string), insertQuery, level, Player_GetAccountID(target));
        mysql_tquery(MySQL_GetHandle(), string);
        Player_SetArmy(playerid, true);
        SendMsgAllF(COLOR_MODERATION, "[ARMY]: %p (%d) is accepted from the army. By the Owner's decision");
    }
    return 1;
}

ACMD:[5]blacklist(playerid, params[])
{
    new target, reason[128], string[256];
    if(sscanf(params, "us[128]", target, reason)) return SendSyntaxMsg(playerid, "/blacklist (name/id) (reason)");
    if(!IsPlayerConnected(target)) return SendErrorMsg(playerid, "Player is not connected");
    if(IsPlayerBlacklisted(target)) return SendErrorMsg(playerid, "Player is blacklisted already");
    if(Player_GetClass(target) == TEAM_ARMY) {
        Class_SelectionState(target, true);
        ForceClassSelection(target);
        TogglePlayerSpectating(target, true);
        TogglePlayerSpectating(target, false);
        Player_SetBoughtSkin(playerid, true);
    }
    static const Query[] = "\
    UPDATE \
        armys \
    SET \
        Blacklisted = %i \
    WHERE \
        u_id = %i \
    ";
    mysql_format(MySQL_GetHandle(), string, sizeof(string), Query, 1, Player_GetAccountID(target));
    mysql_tquery(MySQL_GetHandle(), string);
    Player_SetArmy(target, false);
    Player_SetBlacklist(target, true);
    SendMsgAllF(COLOR_MODERATION, "[ARMY]: %p (%d) has been blacklisted from army by the Owners", target, target);
    SendMsgAllF(COLOR_MODERATION, "Reason: %s", reason);
    SendMsgF(target, COLOR_MODERATION, "[ARMY]: You have been blacklisted from the army.");
    return 1;
}

ACMD:[5]unblacklist(playerid, params[])
{
    new target, string[256];
    if(sscanf(params, "u", target)) return SendSyntaxMsg(playerid, "/unblacklist (name/id)");
    if(!IsPlayerConnected(target)) return SendErrorMsg(playerid, "Player is not connected");
    if(!IsPlayerBlacklisted(target)) return SendErrorMsg(playerid, "Player is not blacklisted");
    static const Query[] = "\
    UPDATE \
        armys \
    SET \
        Blacklisted = %i \
    WHERE \
        u_id = %i \
    ";
    mysql_format(MySQL_GetHandle(), string, sizeof(string), Query, 0, Player_GetAccountID(target));
    mysql_tquery(MySQL_GetHandle(), string);
    Player_SetBlacklist(target, false);
    SendMsgF(playerid, COLOR_MODERATION, "[ARMY]: You have unblacklisted %p (%d) from the army", target, target);
    SendMsgF(target, COLOR_MODERATION, "[ARMY]: You have been unblacklisted from the army.");
    return 1;
}