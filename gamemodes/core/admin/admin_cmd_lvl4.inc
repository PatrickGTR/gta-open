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
        if (sscanf(params, "{s[6]}iii", targetid, level, month))
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
    }
    GivePlayerMoney(playerid, pmoney);
    SendMsgAllF(COLOR_GREEN, "** ADMIN BOT **:"C_WHITE" Administrator gave %p (%d) $%d for", target, target, pmoney);
    SendMsgAllF(COLOR_GREEN, "** ADMIN BOT **:"C_WHITE" reason: %s", reason);
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
    }
    GivePlayerMoney(playerid, -pmoney);
    SendMsgAllF(COLOR_GREEN, "** ADMIN BOT **:"C_WHITE" Administrator fined %p (%d) $%d for", target, target, pmoney);
    SendMsgAllF(COLOR_GREEN, "** ADMIN BOT **:"C_WHITE" reason: %s", reason);
    return 1;
}

ACMD:[4]getmoney(playerid, params[])
{
    new target;
    if(sscanf(params, "u", target)) return SendSyntaxMsg(playerid, "/getmoney [playerid]");
    if(!IsPlayerConnected(target)) {
        return SendErrorMsg(playerid, "Player is not connected");
    }
    SendServerMsgF(playerid, "%p (%d)'s money is $%d", target, target, GetPlayerMoney(playerid));
    return 1;
}