ACMD:[4]setvip(playerid, params[])
{
    new 
        targetid, 
        level, 
        month;

    if (isnull(params))
        return SendSyntaxMsg(playerid, "/setvip month | perma");

    if (!strcmp(params, "month", true, 5))
    {
        if (sscanf(params, "{s[6]}uii", targetid, level, month))
            return SendSyntaxMsg(playerid, "/setvip month <playerid> <Level> <Months>");

        if (targetid == INVALID_PLAYER_ID)
            return SendErrorMsg(playerid, "The player you are trying to set VIP is invalid");

        if (VIP_GetPlayerLevel(targetid) > 0)
            return SendErrorMsg(playerid, "The player you are trying to set VIP has VIP already.");

        if (!(0 <= level < 3))
            return SendErrorMsg(playerid, "Invalid VIP level");

        VIP_GivePlayer(targetid, level, 0, month);

        SendMsgF(targetid, COLOR_LIGHTGREEN, "** VIP ** "C_WHITE"Your VIP level has been set to "C_GREY"%i "C_WHITE"by admin "C_GREY"%p(%i)", level, playerid, playerid);
        SendAdminMsgF("ADMIN "C_GREY"%p "C_WHITE"sets "C_GREY"%p "C_WHITE"VIP level to "C_GREY"%i", playerid, targetid, level);
    }
    if (!strcmp(params, "perma", true, 5))
    {
        if (sscanf(params, "{s[6]}ii", targetid, level))
            return SendSyntaxMsg(playerid, "/setvip perma <playerid> <Level>");

        if (targetid == INVALID_PLAYER_ID)
            return SendErrorMsg(playerid, "The player you are trying to set VIP is invalid");
        
        if (VIP_GetPlayerLevel(targetid) > 0)
            return SendErrorMsg(playerid, "The player you are trying to set VIP has VIP already.");

        if (!(0 <= level < 3))
            return SendErrorMsg(playerid, "Invalid VIP level");

        VIP_GivePlayer(targetid, level, 1, 20);


        SendMsgF(targetid, COLOR_LIGHTGREEN, "** VIP ** "C_WHITE"Your VIP level has been set to "C_GREY"%i "C_WHITE"by admin "C_GREY"%p(%i)", level, playerid, playerid);
        SendAdminMsgF("ADMIN "C_GREY"%p "C_WHITE"sets "C_GREY"%p "C_WHITE"VIP level to "C_GREY"%i", playerid, targetid, level);
    }
    return true;
} 

ACMD:[4]givemoney(playerid, params[])
{
    new target, pmoney, reason[128];
    if(sscanf(params, "uis[128]", target, pmoney, reason)) return SendSyntaxMsg(playerid, "/givemoney [playerid] [money] [reason]");
    if(!IsPlayerConnected(target)) {
        return SendErrorMsg(playerid, "Player is not connected");
    
    GivePlayerMoney(target, pmoney);
    SendMsgAllF(COLOR_MODERATION, "[ADMIN REWARD]: Administrator gave %p (%d) $%d for reason: %s", target, target, pmoney, reason);
    return 1;
}

ACMD:[4]fine(playerid, params[])
{
    new target, pmoney, reason[128];
    if(sscanf(params, "uis[128]", target, pmoney, reason)) return SendSyntaxMsg(playerid, "/fine [playerid] [money] [reason]");
    if(!IsPlayerConnected(target)) {
        return SendErrorMsg(playerid, "Player is not connected");
    }
    if(GetPlayerMoney(playerid) < pmoney) {
        return SendErrorMsg(playerid, "Player doesn't have that much money");
    
    GivePlayerMoney(target, -pmoney);
    SendMsgAllF(COLOR_MODERATION, "[ADMIN FINE]: Administrator fined %p (%d) $%d for", target, target, pmoney);
    SendMsgAllF(COLOR_MODERATION, "[ADMIN FINE]: reason: %s", reason);
    return 1;
}

ACMD:[4]getmoney(playerid, params[])
{
    new target;
    if(sscanf(params, "u", target)) return SendSyntaxMsg(playerid, "/getmoney [playerid]");
    if(!IsPlayerConnected(target)) {
        return SendErrorMsg(playerid, "Player is not connected");
    
    SendServerMsgF(playerid, "%p (%d)'s money is $%d", target, target, GetPlayerMoney(target));
    return 1;
}

ACMD:[4]givearmy(playerid, params[])
{
    new target, level, string[256];
    if(sscanf(params, "ui", target, level)) return SendSyntaxMsg(playerid, "/givearmy (name/id) (1/0)");
    if(!IsPlayerConnected(target)) {
        return SendErrorMsg(playerid, "Player is not connected");
    }
    if(IsPlayerBlacklisted(target)) {
        return SendErrorMsg(playerid, "Player is Blacklisted from army");
    }
    if(GetPlayerScore(target) < 30000) {
        return SendErrorMsg(playerid, "Player's score is not 30000");
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
        SendMsgAllF(COLOR_MODERATION, "[ARMY]: %p (%d) is removed from the army.", target, target);
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
        mysql_format(MySQL_GetHandle(), string, sizeof(string), insertQuery, level, Player_GetAccountID(target), level);
        mysql_tquery(MySQL_GetHandle(), string);
        Player_SetArmy(playerid, true);
        SendMsgAllF(COLOR_MODERATION, "[ARMY]: %p (%d) is accepted from the army.", target, target);
    
    return 1;
}