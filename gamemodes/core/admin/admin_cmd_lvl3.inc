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

forward EventInteriors(playerid, listitem);
public EventInteriors(playerid, listitem)
{
    switch(listitem)
    {
        case 1:
        {
            SetPlayerInterior(playerid, 2);
            SetPlayerPos(playerid, 2567.52,	-1294.59, 1063.25);
        }
        case 2:
        {
            SetPlayerInterior(playerid, 15);
            SetPlayerPos(playerid, -1394.20, 987.62, 1023.96);
        }
        case 3:
        {
            SetPlayerInterior(playerid, 4);
            SetPlayerPos(playerid, -1424.9319, -664.5869, 1059.8585);
        }
        case 4:
        {
            SetPlayerInterior(playerid, 7);
            SetPlayerPos(playerid, -1395.958, -208.197,	1051.170);
        }
        case 5:
        {
            SetPlayerInterior(playerid, 14);
            SetPlayerPos(playerid, -1410.72, 1591.16, 1052.53);
        }
    }
    return 1;
}

ShowEvenInteriors(playerid)
{
    TextMenu_Create(playerid, "EventInteriors", "Event Interiors");
    TextMenu_Add(playerid, "~w~Big Smoke's Crack Palace");
    TextMenu_Add(playerid, "~w~Bloodbowl Stadium");
    TextMenu_Add(playerid, "~w~Dirt Bike Stadium");
    TextMenu_Add(playerid, "~w~8 Track Stadium");
    TextMenu_Add(playerid, "~w~Kickstart Stadium");
    TextMenu_Show(playerid);
    return 1;
}

ACMD:[3]eventint(playerid, params[])
{
    ShowEvenInteriors(playerid);
    return 1;
}
