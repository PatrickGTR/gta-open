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

ACMD:[1]get(playerid, params[])
{
	new targetid;
	new Float:pos[4];
	if(sscanf(params, "u", targetid)) return SendSyntaxMsg(playerid, "/get [player]");
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
	if(target == playerid) return SendErrorMsg(playerid, "You can't get yourself");
	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(target));
	SetPlayerInterior(playerid, GetPlayerInterior(target));
	GetPlayerPos(target, pos[0], pos[1], pos[2]);
	SetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	SendAdminCmdUsage(playerid, "/goto", params);
	return 1;
}

ACMD:[1]a(playerid, params[])
{
	new msg[128];
	if(sscanf(params, "s", msg)) return SendSyntaxMsg(playerid, "/a [message]");
	foreach(new i : Player)
    {
        if (i != INVALID_PLAYER_ID)
        {
            if(Admin_GetPlayerLevel(i) > 0)
            {    
                SendMsgF(i, COLOR_BLUE, "[ADMIN] %p (%d) "C_WHITE": %s", playerid, playerid, msg);
            }
        }
    }
	return 1;
}