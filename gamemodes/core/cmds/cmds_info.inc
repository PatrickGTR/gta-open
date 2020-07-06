CMD:info(playerid, params[])
{
    new target;
    if(sscanf(params, "u", target))
    {
        ShowPlayerInfo(playerid);
    }
    else
    {
        if(!IsPlayerConnected(target)) {
            return SendErrorMsg(playerid, "Player is not connected");
        }
        ShowInfoOfPlayer(playerid, target);
    }
    return 1;
}

ShowPlayerInfo(playerid)
{
    new string[128], location[MAX_MAP_ZONE_NAME + 12];
    Player_GetLocation(playerid, location);
    TextInfo_Create(playerid, "PlayerInfo", "Player Info");
	format(string, sizeof(string), "~r~Name: ~w~%p (%d)~n~", playerid, playerid);
	TextInfo_Add(playerid, string);
	format(string, sizeof(string), "~r~Location: ~w~%s~n~", location);
	TextInfo_Add(playerid, string);
	format(string, sizeof(string), "~r~Class: ~w~%s~n~", Player_GetClassName(playerid));
	TextInfo_Add(playerid, string);
    if(Player_GetClass(playerid) == TEAM_CIVILIAN)
    {
        format(string, sizeof(string), "~r~Job: ~w~%s~n~", Player_Jobname(playerid));
	    TextInfo_Add(playerid, string);
    }
	TextInfo_Show(playerid);
    return 1;
}

ShowInfoOfPlayer(playerid, target)
{
    new string[128], location[MAX_MAP_ZONE_NAME + 12];
    Player_GetLocation(target, location);
    TextInfo_Create(playerid, "PlayerInfo", "Player Info");
	format(string, sizeof(string), "~r~Name: ~w~%p (%d)~n~", target, target);
	TextInfo_Add(playerid, string);
	format(string, sizeof(string), "~r~Location: ~w~%s~n~", location);
	TextInfo_Add(playerid, string);
	format(string, sizeof(string), "~r~Class: ~w~%s~n~", Player_GetClassName(target));
	TextInfo_Add(playerid, string);
    if(Player_GetClass(target) == TEAM_CIVILIAN)
    {
        format(string, sizeof(string), "~r~Job: ~w~%s~n~", Player_Jobname(target));
	    TextInfo_Add(playerid, string);
    }
	TextInfo_Show(playerid);
    return 1;
}