CMD:info(playerid, params[])
{
    new target;
    if(sscanf(params, "u", target))
    {
        Player_ShowInfo(playerid, playerid);
        return 1;
    }
    
    if(!IsPlayerConnected(target)) {
        SendErrorMsg(playerid, "Player is not connected");
        return 1;
    }
        
    Player_ShowInfo(playerid, target);
    return 1;
}

Player_ShowInfo(playerid, target)
{
    new string[256], location[MAX_MAP_ZONE_NAME + 12];
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
    format(string, sizeof(string), "~r~Kills: ~w~%d~n~", Player_GetKills(target));
    TextInfo_Add(playerid, string);
    format(string, sizeof(string), "~r~Deaths: ~w~%d~n~", Player_GetDeaths(target));
    TextInfo_Add(playerid, string);
    format(string, sizeof(string), "~r~Ratio: ~w~%.2f", floatdiv(Player_GetKills(target), Player_GetDeaths(target)));
	TextInfo_Add(playerid, string);
    TextInfo_Show(playerid);
    return 1;
}