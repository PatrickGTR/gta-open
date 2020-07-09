ACMD:[3]getallciv(playerid, params[])
{
    new Float:pos[4];
    foreach(new i : Player)
    {
        if(Player_GetClass(i) == TEAM_CIVILIAN)
        {
            GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
            SetPlayerPos(i, pos[0], pos[1], pos[2]);
        }
    }
    SendAdminCmdUsage(playerid, "/getallciv", params);
    return 1;
}

ACMD:[3]disarm(playerid, params[])
{
    new target;
    if(sscanf(params, "u", target)) return SendSyntaxMsg(playerid, "/disarm (name/id)");
    if(!IsPlayerConnected(target)) {
        return SendErrorMsg(playerid, "Player is not connected");
    }
    ResetPlayerWeapons(target);
    SendMsgF(playerid, COLOR_MODERATION, "[ADMIN DISARM]: You have disarmed %p (%d)", target, target);
    SendMsgF(target, COLOR_MODERATION, "[ADMIN DISARM]: You have been disarmed by an admin");
    SendAdminCmdUsage(playerid, "/getallciv", params);
    return 1;
}

ACMD:[3]sethealth(playerid, params[])
{
    new target, Float:health;
    if(sscanf(params, "uf", target, health)) return SendSyntaxMsg(playerid, "/setheatlh (name/id) (health)");
    SendMsgF(playerid, COLOR_MODERATION, "[ADMIN HEAL]: %p (%d)'s health has been set to %f", target, target, health);
    SendMsgF(target, COLOR_MODERATION, "[ADMIN HEAL]: Your health has been set to %f", health);
    SetPlayerHealth(playerid, health);
    SendAdminCmdUsage(playerid, "/sethealth", params);
    return 1;
}

ACMD:[3]setarmour(playerid, params[])
{
    new target, Float:armour;
    if(sscanf(params, "uf", target, armour)) return SendSyntaxMsg(playerid, "/setarmour (name/id) (armour)");
    SendMsgF(playerid, COLOR_MODERATION, "[ADMIN]: %p (%d)'s armour has been set to %f", target, target, armour);
    SendMsgF(target, COLOR_MODERATION, "[ADMIN]: Your armour has been set to %f", armour);
    SetPlayerArmour(playerid, armour);
    SendAdminCmdUsage(playerid, "/setarmour", params);
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

ACMD:[3]setvirtualworld(playerid, params[])
{
    new vm;
    if(sscanf(params, "i", vm)) return SendSyntaxMsg(playerid, "/setvirtualworld (virtual world)");
    SetPlayerVirtualWorld(playerid, vm);
    return 1;
}