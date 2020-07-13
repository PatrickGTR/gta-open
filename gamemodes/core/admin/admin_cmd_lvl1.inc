ACMD:[1]acmds(playerid, params[])
{
	new
		tmp_string[1024];

	//strcat(tmp_string, "/a [message] - Staff chat channel");

	if (Admin_GetPlayerLevel(playerid) >= ADM_LVL_5)
	{
		strcat(tmp_string, "\n\n"C_YELLOW"(level 5)"C_WHITE"\n");
		strcat(tmp_string, adminCommands[4]);
	}
	if (Admin_GetPlayerLevel(playerid) >= ADM_LVL_4)
	{
		strcat(tmp_string, "\n\n"C_YELLOW"(level 4)"C_WHITE"\n");
		strcat(tmp_string, adminCommands[3]);
	}
	if (Admin_GetPlayerLevel(playerid) >= ADM_LVL_3)
	{
		strcat(tmp_string, "\n\n"C_YELLOW"(level 3)"C_WHITE"\n");
		strcat(tmp_string, adminCommands[2]);
	}
	if (Admin_GetPlayerLevel(playerid) >= ADM_LVL_2)
	{
		strcat(tmp_string, "\n\n"C_YELLOW"(level 2)"C_WHITE"\n");
		strcat(tmp_string, adminCommands[1]);
	}
	if (Admin_GetPlayerLevel(playerid) >= ADM_LVL_1)
	{
		strcat(tmp_string, "\n\n"C_YELLOW"(level 1)"C_WHITE"\n");
		strcat(tmp_string, adminCommands[0]);
	}
	SendAdminCmdUsage(playerid, "/acmds", params);
	Dialog_Show(playerid, DIALOG_STYLE_MSGBOX, "Admin Commands List", tmp_string, "Close", "");
	return 1;
}

forward AdminListMenu(playerid, listitem);
public AdminListMenu(playerid, listitem)
{
	new tmpString[24];
	format(tmpString, sizeof(tmpString), "AdminCount_%i", listitem);
	new targetid = GetPVarInt(playerid, tmpString);

	if(IsPlayerConnected(targetid)) {
		new
			location[MAX_MAP_ZONE_NAME + 12],
			string[128];
		Player_GetLocation(targetid, location);
		TextInfo_Create(playerid, "AdminList", "Player Info");
		format(string, sizeof(string), "~r~Name: ~w~%p (%d)~n~", targetid, targetid);
		TextInfo_Add(playerid, string);
		format(string, sizeof(string), "~r~Location: ~w~%s~n~", location);
		TextInfo_Add(playerid, string);
		format(string, sizeof(string), "~r~Class: ~w~%s~n~", Player_GetClassName(targetid));
		TextInfo_Add(playerid, string);
		if(Player_GetClass(targetid) == TEAM_CIVILIAN)
    	{
        	format(string, sizeof(string), "~r~Job: ~w~%s~n~", Player_Jobname(targetid));
	    	TextInfo_Add(playerid, string);
    	}
		TextInfo_Show(playerid);
	}
	return 1;
}

ACMD:[1]admins(playerid, params[])
{
	new onlineadmins = 0;
	new tmpString[100];
	TextMenu_Create(playerid, "AdminListMenu", "Admins");
	foreach(new i : Player)
	{
		if(Admin_GetPlayerLevel(i) > 0) 
		{
			format(tmpString, sizeof(tmpString),
            "%p (%d) Admin Level: %s",
        	i, i, Admin_GetRankName(i));
			TextMenu_Add(playerid, tmpString);
			
			format(tmpString, sizeof(tmpString), "AdminCount_%i", onlineadmins);
			SetPVarInt(playerid, tmpString, i);
			onlineadmins++;
		}
	}
	if(onlineadmins == 0) {
		return SendServerMsg(playerid, "No online admins");
	}
	else {
		TextMenu_Show(playerid);
	}
	return true;
}

ACMD:[1]get(playerid, params[])
{
	new targetid;
	new Float:pos[4];
	if(sscanf(params, "u", targetid)) return SendSyntaxMsg(playerid, "/get [player]");
	if(!IsPlayerConnected(targetid)) {
		return SendErrorMsg(playerid, "Player is not connected");
	}
	if(targetid == playerid) return SendErrorMsg(playerid, "You can't get yourself");
	SetPlayerVirtualWorld(targetid, GetPlayerVirtualWorld(playerid));
	SetPlayerInterior(targetid, GetPlayerInterior(playerid));
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	SetPlayerPos(targetid, pos[0], pos[1], pos[2]);
	SendAdminCmdUsage(playerid, "/get", params);
	return 1;
}

ACMD:[1]goto(playerid, params[])
{
	new target;
	new Float:pos[4];
	if(sscanf(params, "u", target)) return SendSyntaxMsg(playerid, "/gotop (playerid)");
	if(!IsPlayerConnected(target)) {
		return SendErrorMsg(playerid, "Player is not connected");
	}
	if(target == playerid) return SendErrorMsg(playerid, "You can't goto yourself");
	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(target));
	SetPlayerInterior(playerid, GetPlayerInterior(target));
	GetPlayerPos(target, pos[0], pos[1], pos[2]);
	SetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	SendAdminCmdUsage(playerid, "/goto", params);
	return 1;
}

ACMD:[1]kick(playerid, params[])
{
	new target, reason[128];
	if(sscanf(params, "us[128]", target, reason)) return SendSyntaxMsg(playerid, "/kick (name/in) (reason)");
	if(!IsPlayerConnected(target)) {
		return SendErrorMsg(playerid, "Player not connected");
	}
	SendMsgAllF(COLOR_MODERATION, "[ADMIN KICK]: %p (%d) has been kicked for: %s", target, target, reason);
	SendMsgF(target, COLOR_MODERATION, "[ADMIN KICK]: You have Been Kicked for Reason: %s", reason);
	defer KickTimer(target);
	SendAdminCmdUsage(playerid, "/kick", params);
	return 1;
}

ACMD:[1]setwanted(playerid, params[])
{
	new target, level;
	if(sscanf(params, "ui", target, level)) return SendSyntaxMsg(playerid, "/setwanted (name/id) (wanted level)");
	if(!IsPlayerConnected(target)) {
		return SendErrorMsg(playerid, "Player is not connected");
	}
	if(level != 0 && Player_IsLEO(playerid)) {
		return SendErrorMsg(playerid, "You cant give Enforcers wanted level");
	}
	PLAYER_SetPlayerWantedLevel(target, level);
	SendMsgF(playerid, COLOR_MODERATION, "[ADMIN]: %p (%d)'s wanted level has been set to %d", target, target, level);
	SendMsgF(target, COLOR_MODERATION, "[ADMIN]: Your wanted level has been set to %d by Admin", level);
	SendAdminCmdUsage(playerid, "/setwanted", params);
	return 1;
}

ACMD:[1]asay(playerid, params[])
{
	new text[128];
	if(sscanf(params, "s[128]", text)) return SendSyntaxMsg(playerid, "/asay (text)");
	SendMsgAllF(COLOR_MODERATION, "[ADMIN]: %s", text);
	SendAdminCmdUsage(playerid, "/asay", params);
	return 1;
}

ACMD:[1]respawn(playerid, params[])
{
	new target;
	if(sscanf(params, "u", target)) return SendSyntaxMsg(playerid, "/respawn (name/id)");
	TogglePlayerSpectating(target, true);
	ForceSpawnPlayer(target);
	SendAdminCmdUsage(playerid, "/respawn", params);
	return 1;
}

ACMD:[1]freeze(playerid, params[])
{
	new target, level, reason[128];
	if(sscanf(params, "uiS(No Reason)[128]", target, level, reason)) return SendSyntaxMsg(playerid, "/freeze (name/id) (1/0) (reason)");
	if(!IsPlayerConnected(target)) return SendErrorMsg(playerid, "Player is not connected");
	if(level < 0 || level > 1) {
		return SendErrorMsg(playerid, "Use 0 to unfreeze the player use 1 to freeze");
	}
	if(level == 1) {
		TogglePlayerControllable(playerid, false);
		SendMsgAllF(COLOR_MODERATION, "[ADMIN FREEZE]: %p (%d) has been freeze by an Admin for: %s", target, target, reason);
	}
	if(level == 0) {
		TogglePlayerControllable(playerid, true);
		SendMsgAllF(COLOR_MODERATION, "[ADMIN UNFREEZE]: %p (%d) has been unfreezed by an Admin", target, target);
	}
	SendAdminCmdUsage(playerid, "/freeze", params);
 	return 1;
}

ACMD:[1]akill(playerid, params[])
{
	new target;
	new Float:x, Float:y, Float:z;
	if(sscanf(params, "u", target)) return SendSyntaxMsg(playerid, "/akill (name/id)");
	if(!IsPlayerConnected(target)) return SendErrorMsg(playerid, "Player is not connected");
	SetPlayerHealth(target, 0);
	GetPlayerPos(target, x, y, z);
	SendMsgAllF(COLOR_BROWN, "%p (%d) Has Died by the Hand Of God", target, target);
	CreateExplosion(x, y, z, 12, 10.0);
	SendAdminCmdUsage(playerid, "/akill", params);
	return 1;
}

ACMD:[1]afix(playerid, params[])
{
	if(!IsPlayerInAnyVehicle(playerid)) return SendErrorMsg(playerid, "You're not in any vehicle");
	RepairVehicle(GetPlayerVehicleID(playerid));
	SendAdminCmdUsage(playerid, "/afix", params);
	return 1;
}