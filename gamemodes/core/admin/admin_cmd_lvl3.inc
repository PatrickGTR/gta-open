ACMD:[3]setname(playerid, params[])
{
    new
        targetid,
        newName[MAX_PLAYER_NAME + 1],
        string[128];

    if(sscanf(params, "us[25]", targetid, newName)) {
        return SendSyntaxMsg(playerid, "/setname (name/id) (newname)");
    }

    if(!IsPlayerConnected(targetid)) {
        return SendErrorMsg(playerid, "Player not connected");
    }

    mysql_format(MySQL_GetHandle(), string, sizeof(string), "UPDATE players SET username = '%e' WHERE u_id = %i", newName, Player_GetAccountID(targetid));
    mysql_tquery(MySQL_GetHandle(), string);

    SendMsgF(targetid, COLOR_MODERATION, "[ADMIN]: Your name has been changed to %s", newName);
    SendMsgF(playerid, COLOR_MODERATION, "[ADMIN]: You have set %p (%d)'s name to %s", targetid, targetid, newName);

    SetPlayerName(targetid, newName);
    return 1;
}

ACMD:[3]setarmy(playerid, params[]) {
    new
        targetid;

    if(sscanf(params, "u", targetid)) {
        return SendSyntaxMsg(playerid, "/setarmy <name/id>");
    }

    if(!IsPlayerConnected(targetid)) {
        return SendErrorMsg(playerid, "Player not connected");
    }

    if(!Player_AddToArmyDB(targetid)) {
        return SendErrorMsg(playerid, "Player is already in army");
    }

    SendMsgF(targetid, COLOR_MODERATION, "[ADMIN]: %p(%i) added you to the army", playerid, playerid);
    SendMsgF(playerid, COLOR_MODERATION, "[ADMIN]: You have been added to the army by %p(%i)", targetid, targetid);
    return 1;
}

ACMD:[3]revokearmy(playerid, params[]) {
    new
        targetid;

    if(sscanf(params, "u", targetid)) {
        return SendSyntaxMsg(playerid, "/setarmy <name/id>");
    }

    if(!IsPlayerConnected(targetid)) {
        return SendErrorMsg(playerid, "Player not connected");
    }

    if(!Player_RemoveFromArmyDB(targetid)) {
        return SendErrorMsg(playerid, "Player is not in army");
    }

    SendMsgF(targetid, COLOR_MODERATION, "[ADMIN]: %p(%i) removed you from the army", playerid, playerid);
    SendMsgF(playerid, COLOR_MODERATION, "[ADMIN]: You have been removed from the army by %p(%i)", targetid, targetid);
    return 1;
}

ACMD:[3]getallciv(playerid, params[])
{
    new
        Float:x,
        Float:y,
        Float:z;

    foreach(new i : Player) {
        if(Player_GetClass(i) == TEAM_CIVILIAN) {
            GetPlayerPos(playerid, x, y, z);
            SetPlayerPos(i, x, y + i, z);
        }
    }
    return 1;
}

ACMD:[3]disarm(playerid, params[])
{
    new
        targetid;

    if(sscanf(params, "u", targetid)) {
        return SendSyntaxMsg(playerid, "/disarm (name/id)");
    }

    if(!IsPlayerConnected(targetid)) {
        return SendErrorMsg(playerid, "Player is not connected");
    }

    SendMsgF(playerid, COLOR_MODERATION, "[ADMIN DISARM]: You have disarmed %p (%d)", targetid, targetid);
    SendMsgF(targetid, COLOR_MODERATION, "[ADMIN DISARM]: You have been disarmed by an admin");

    ResetPlayerWeapons(targetid);
    return 1;
}

ACMD:[3]sethealth(playerid, params[])
{
    new
        targetid,
        Float:amount;

    if(sscanf(params, "uf", targetid, amount)) {
        return SendSyntaxMsg(playerid, "/setheatlh (name/id) (health)");
    }

    if(!IsPlayerConnected(targetid)) {
        return SendErrorMsg(playerid, "Player is not connected");
    }

    SendMsgF(playerid, COLOR_MODERATION, "[ADMIN HEAL]: %p (%d)'s health has been set to %f", targetid, targetid, amount);
    SendMsgF(targetid, COLOR_MODERATION, "[ADMIN HEAL]: Your health has been set to %f", amount);

    SetPlayerHealth(targetid, amount);
    return 1;
}

ACMD:[3]setarmour(playerid, params[])
{
    new
        targetid,
        Float:amount;

    if(sscanf(params, "uf", targetid, amount)) {
        return SendSyntaxMsg(playerid, "/setarmour (name/id) (armour)");
    }

    if(!IsPlayerConnected(targetid)) {
        return SendErrorMsg(playerid, "Player is not connected");
    }

    SendMsgF(playerid, COLOR_MODERATION, "[ADMIN]: %p (%d)'s armour has been set to %f", targetid, targetid, amount);
    SendMsgF(targetid, COLOR_MODERATION, "[ADMIN]: Your armour has been set to %f", amount);

    SetPlayerArmour(targetid, amount);
    return 1;
}
