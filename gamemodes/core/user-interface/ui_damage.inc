#include <YSI_Data\y_bit>
#include <YSI_Data\y_iterate>
#include <YSI_Coding\y_timers>
#include <YSI_Coding\y_hooks>
#include <formatex>

static
	PlayerText:dmg_Reciever[MAX_PLAYERS],
	PlayerText:dmg_Giver[MAX_PLAYERS],
	Float:dmg_TotalRecieved[MAX_PLAYERS][MAX_PLAYERS],
	Float:dmg_TotalGiven[MAX_PLAYERS][MAX_PLAYERS],
	BitArray:dmg_AlreadyShowing<MAX_PLAYERS>;

hook OnPlayerConnect(playerid) {

	static
		Float:y = 340.0;

	dmg_Giver[playerid] = CreatePlayerTextDraw   (playerid, 170.0, y,"~w~Player ~y~(Deagle) ~g~+46");
	PlayerTextDrawFont                           (playerid, dmg_Giver[playerid], 1);
	PlayerTextDrawLetterSize                     (playerid, dmg_Giver[playerid], 0.18, 0.18 * 4);
	PlayerTextDrawBackgroundColor                (playerid, dmg_Giver[playerid], TD_OUTLINE_COLOUR);
	PlayerTextDrawColor                          (playerid, dmg_Giver[playerid], -1);
	PlayerTextDrawSetProportional                (playerid, dmg_Giver[playerid], 1);
	PlayerTextDrawSetOutline                     (playerid, dmg_Giver[playerid],1);
	PlayerTextDrawSetShadow                      (playerid, dmg_Giver[playerid],0);

	dmg_Reciever[playerid] = CreatePlayerTextDraw(playerid, 380.0, y,"~w~Player ~y~(Deagle) ~r~-46");
	PlayerTextDrawFont                           (playerid, dmg_Reciever[playerid], 1);
	PlayerTextDrawLetterSize                     (playerid, dmg_Reciever[playerid], 0.18, 0.18 * 4);
	PlayerTextDrawBackgroundColor                (playerid, dmg_Reciever[playerid], TD_OUTLINE_COLOUR);
	PlayerTextDrawColor                          (playerid, dmg_Reciever[playerid], -1);
	PlayerTextDrawSetProportional                (playerid, dmg_Reciever[playerid], 1);
	PlayerTextDrawSetOutline                     (playerid, dmg_Reciever[playerid],1);
	PlayerTextDrawSetShadow                      (playerid, dmg_Reciever[playerid],0);

	Bit_Set(dmg_AlreadyShowing, playerid, false);
	foreach(new i : Player) {
		dmg_TotalRecieved[playerid][i] =
		dmg_TotalGiven[playerid][i]    = 0.0;
	}
	return 1;
}

hook OnPlayerDeathEx(playerid, killerid, reason, Float: damage, bodypart) {
	// If the player who has the damage UI present died, hide the damage UI.
	if(Bit_Get(dmg_AlreadyShowing, playerid)) {
		defer HideGiveDamageUI(playerid, INVALID_PLAYER_ID, 5000);
		defer HideTakeDamageUI(playerid, INVALID_PLAYER_ID, 5000);
		Bit_Set(dmg_AlreadyShowing, playerid, false);

		foreach(new i : Player) {
			dmg_TotalRecieved[playerid][i] =
			dmg_TotalGiven[playerid][i]    = 0.0;
		}
	}
}

ProcessTakeDamageUI(playerid, issuerid, Float:damage) {
	if(!Bit_Get(dmg_AlreadyShowing, playerid)) {
		Bit_Set(dmg_AlreadyShowing, playerid, true);
		defer HideTakeDamageUI(playerid, issuerid, 5000);
	}

	new string[128];

	if(issuerid == INVALID_PLAYER_ID) {
		format(string, sizeof(string), "%s~b~Collision ~r~%0.2f", string, damage);
	}
	else {

		dmg_TotalRecieved[playerid][issuerid] += damage;

		if(dmg_TotalRecieved[playerid][issuerid] != dmg_TotalRecieved[playerid][issuerid]) {
			format(string, sizeof(string), "%s%p ~y~(%W) ~r~-%0.2f~n~", string, issuerid, GetPlayerWeapon(issuerid), dmg_TotalRecieved[playerid][issuerid]);
		}
		else {
			format(string, sizeof(string), "%p ~y~(%W) ~r~-%0.2f~n~", issuerid, GetPlayerWeapon(issuerid), dmg_TotalRecieved[playerid][issuerid]);
		}
	}
	PlayerTextDrawShow(playerid, dmg_Reciever[playerid]);
	PlayerTextDrawSetString(playerid, dmg_Reciever[playerid], string);
	return 1;
}

ProcessGiveDamageUI(playerid, damageid, Float:damage) {

	// Avoid running the timer, if the damage UI is already present.
	if(!Bit_Get(dmg_AlreadyShowing, playerid)) {
		Bit_Set(dmg_AlreadyShowing, playerid, true);
		defer HideGiveDamageUI(playerid, damageid, 5000);
	}

	new string[128];

	dmg_TotalGiven[playerid][damageid] += damage;
	PlayerTextDrawShow(playerid, dmg_Giver[playerid]);
	if(dmg_TotalGiven[playerid][damageid] != dmg_TotalGiven[playerid][damageid]) {
		format(string, sizeof(string), "%s%p ~y~(%W) ~g~+%0.2f~n~", string, damageid, GetPlayerWeapon(playerid), dmg_TotalGiven[playerid][damageid]);
	}
	else {
		format(string, sizeof(string), "%p ~y~(%W) ~g~+%0.2f~n~", damageid, GetPlayerWeapon(playerid), dmg_TotalGiven[playerid][damageid]);
	}
	PlayerTextDrawSetString(playerid, dmg_Giver[playerid], string);
}

hook OnPlayerDamagePlayer(playerid, damagedid, Float: amount, weaponid, bodypart) {
    ProcessTakeDamageUI(damagedid, playerid, amount);
    ProcessGiveDamageUI(playerid, damagedid, amount);
	return 1;
}

hook OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart) {
	if(weaponid == WEAPON_COLLISION) { // Collision (Mainly fall damage)
		ProcessTakeDamageUI(playerid, INVALID_PLAYER_ID, amount);
	}
	return 1;
}

timer HideGiveDamageUI[seconds](playerid, damageid, seconds) {
	#pragma unused seconds

	PlayerTextDrawHide(playerid, dmg_Giver[playerid]);
	Bit_Set(dmg_AlreadyShowing, playerid, false);
	if(damageid != INVALID_PLAYER_ID) {
		dmg_TotalGiven[playerid][damageid] = 0.0;
	}
}

timer HideTakeDamageUI[seconds](playerid, issuerid, seconds) {
	#pragma unused seconds

	PlayerTextDrawHide(playerid, dmg_Reciever[playerid]);
	Bit_Set(dmg_AlreadyShowing, playerid, false);

	if(issuerid != INVALID_PLAYER_ID) {
		dmg_TotalRecieved[playerid][issuerid] = 0.0;
	}
}