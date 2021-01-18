

ACMD:[1]get(playerid, params[])
{
	new
		targetid;

	if(sscanf(params, "u", targetid)) {
		return SendSyntaxMsg(playerid, "/get <playerid>");
	}

	if(!IsPlayerConnected(targetid)) {
		return SendErrorMsg(playerid, "Player is not connected");
	}

	if(targetid == playerid) {
		return SendErrorMsg(playerid, "You can't get yourself");
	}

	new
		Float:x,
		Float:y,
		Float:z;
	GetPlayerPos(playerid, x, y, z);

	SetPlayerPos(targetid, x, y, z);
	SetPlayerVirtualWorld(targetid, GetPlayerVirtualWorld(playerid));
	SetPlayerInterior(targetid, GetPlayerInterior(playerid));
	return 1;
}

ACMD:[1]goto(playerid, params[])
{
	new
		targetid;

	if(sscanf(params, "u", targetid)) {
		return SendSyntaxMsg(playerid, "/gotop (playerid)");
	}

	if(!IsPlayerConnected(targetid)) {
		return SendErrorMsg(playerid, "Player is not connected");
	}

	if(targetid == playerid) {
		return SendErrorMsg(playerid, "You can't goto yourself");
	}

	new
		Float:x,
		Float:y,
		Float:z;
	GetPlayerPos(targetid, x, y, z);

	SetPlayerPos(playerid, x, y, z);
	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetid));
	SetPlayerInterior(playerid, GetPlayerInterior(targetid));
	return 1;
}

ACMD:[1]kick(playerid, params[])
{
	new
		targetid,
		reason[32];

	if(sscanf(params, "uS[32](No Reason)", targetid, reason)) {
		return SendSyntaxMsg(playerid, "/kick (name/in) (reason)");
	}

	if(!IsPlayerConnected(targetid)) {
		return SendErrorMsg(playerid, "Player is not connected");
	}

	SendMsgAllF(COLOR_MODERATION, "[ADMIN KICK]: %p (%d) has been kicked for: %s", targetid, targetid, reason);
	SendMsgF(targetid, COLOR_MODERATION, "[ADMIN KICK]: You have Been Kicked for: %s", reason);
	Kick(targetid);
	return 1;
}

ACMD:[1]setwanted(playerid, params[])
{
	new
		targetid,
		level;

	if(sscanf(params, "ui", targetid, level)) {
		return SendSyntaxMsg(playerid, "/setwanted (name/id) (wanted level)");
	}
	if(!IsPlayerConnected(targetid)) {
		return SendErrorMsg(playerid, "Player is not connected");
	}
	if(level != 0 && Player_IsLEO(targetid)) {
		return SendErrorMsg(playerid, "You cant give Enforcers wanted level");
	}
	SetPlayerWantedLevel(targetid, level);
	SendMsgF(playerid, COLOR_MODERATION, "[ADMIN]: %p (%d)'s wanted level has been set to %d", targetid, targetid, level);
	SendMsgF(targetid, COLOR_MODERATION, "[ADMIN]: Your wanted level has been set to %d by Admin", level);
	return 1;
}

ACMD:[1]respawn(playerid, params[])
{
	new target;
	if(sscanf(params, "u", target)) return SendSyntaxMsg(playerid, "/respawn (name/id)");
	TogglePlayerSpectating(target, true);
	ForceSpawnPlayer(target);
	return 1;
}

ACMD:[1]freeze(playerid, params[])
{
	new
		targetid,
		bool:freezeState;

	if(sscanf(params, "ul", targetid, freezeState)) {
		return SendSyntaxMsg(playerid, "/freeze (name/id) (0/1)");
	}

	if(!IsPlayerConnected(targetid)) {
		return SendErrorMsg(playerid, "Player is not connected");
	}

	SendMsgAllF(
		COLOR_MODERATION,
		"[ADMIN FREEZE]: %p(%d) has been %s by Admin %p(%d)",
		targetid,
		targetid,
		(freezeState) ? ("frozen") : ("unfrozen"),
		playerid,
		playerid
	);

	// reverse it
	// because TogglePlayerControllable function
	// uses 0 to freeze and 1 to unfreeze while
	// the command takes 0 to unfreeze, 1 to freeze.
	TogglePlayerControllable(targetid, !freezeState);
 	return 1;
}

ACMD:[1]akill(playerid, params[])
{
	new
		targetid,
		Float:x,
		Float:y,
		Float:z;

	if(sscanf(params, "u", targetid)) {
		return SendSyntaxMsg(playerid, "/akill (name/id)");
	}

	if(!IsPlayerConnected(targetid)) {
		return SendErrorMsg(playerid, "Player is not connected");
	}

	GetPlayerPos(targetid, x, y, z);
	CreateExplosion(x, y, z, 12, 10.0);
	SetPlayerHealth(targetid, 0);

	SendMsgAllF(COLOR_BROWN, "%p(%d) Has died by hand of GOD", targetid, targetid);
	return 1;
}

ACMD:[1]afix(playerid, params[])
{
	if(!IsPlayerInAnyVehicle(playerid)) return SendErrorMsg(playerid, "You're not in any vehicle");
	RepairVehicle(GetPlayerVehicleID(playerid));
	return 1;
}