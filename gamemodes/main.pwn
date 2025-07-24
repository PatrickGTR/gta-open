// Patrick Dave Subang (c) 2020 April
// Github -> https://github.com/PatrickGTR

// Ervin Lance Zamora (c) 2020 April
// Github -> https://github.com/CnRXoMoX

// Credits to these people, made the production easier.
// Southclaw, Y_Less, maddinatOr, SyS, Zeex, Slice, Lorenc

// TextdrawLetterSize Rule -> Thanks to DamianC
// Letter-size-y = letter-size-x * 4
// For a nice font display
#define SAMP_COMPAT

#if 0
	// called when player successfully logged in.
	forward OnPlayerLogin(playerid);

	// called when player successfully registered.
	forward OnPlayerRegister(playerid);

	// called when player's ip/name/gcpi wasn't found in the ban database.
	forward OnPlayerPassedBanCheck(playerid);

	// called every second per player (like OnPlayerUpdate but not as intensive.)
	forward OnPlayerSecondUpdate(playerid);

	// called when player spawns for the first time after initial connection.
	forward OnPlayerFirstSpawn(playerid);

	// called every 2 minutes for datas that need to be saved frequently.
	forward OnPlayerAutoSave(playerid);

	// called when player has robbed another player.
	forward OnPlayerRobPlayer(playerid, targetid, moneyTaken);

	// called when player has successfully robbed a store.
	forward OnPlayerRobStore(playerid, moneyTaken);

	// called when c4 has been detonated.
	forward OnExplosiveDetonate(playerid, Float: x, Float: y, Float: z);

	// called every second.
	forward OnServerSecondUpdate();

	// called when MySQL successfully connects. (mainly used to setup tables & prepare statements)
	forward OnMySQLConnected();

	// called before MySQL disconnects (before mysql_close specifically)
	forward OnMySQLPreClose();

	// called when the in-game week resets.
	forward OnServerWeekReset();

	// called when the in-game day resets.
	forward OnServerDayReset(const day[]);
#endif


// Custom Functions

#if 0
	// playerid -> player to give score.
	// score -> amount of score to give.
	// save -> false by default, toggle to allow saving.
	Player_GiveScore(playerid, score, bool:save = false);

	// playerid -> player to remove score.
	// score -> how much you want to remove from the player.
	Player_RemoveScore(playerid, score);
#endif

// Main
#include <constants>

// Libraries
#include <a_mysql>
#include <samp_bcrypt>

// YSI
#include <YSI_Core\y_utils>
#include <YSI_Coding\y_inline>
#include <YSI_Coding\y_timers>
#include <YSI_Data\y_bit>
#include <YSI_Data\y_iterate>

#include <YSI_Extra\y_inline_mysql>
#include <YSI_Extra\y_inline_bcrypt>

// Legacy Includes
#include <EVF>
#include <progress2>


#include <ini>

// #include <env>
#include <streamer>
#include <logger>
#include <mysql_prepared>
#include <map-zones>
//#include <formatex>

// Gamemode Scripts

#include <init>

#if SETUP_TABLE
	#include <tables>
#endif

#include <utils>
#include <user-interface>
#include <anti-cheat> // w.i.p
#include <server>
#include <account>
#include <player>
#include <houses>
#include <admin>
#include <system>
#include <chat> // chat & messaging
#include <cmds>
#include <mapping>

#include <gangs>

// Will be called after the rest ^
public OnGameModeInit() {
	Message_SetTime(5);
    Message_Add("Welcome to GTA:OPEN");
    Message_Add("You like GTA:OPEN? Add us to your favourites!");
	Message_Add("Check our discord server discord.gg/fhN3q4J6Qr");
    Message_Add("Help keep the server alive by donating!");


	SendRconCommand("hostname "#SERVER_NAME " v" #SCRIPT_VERSION_MAJOR "." #SCRIPT_VERSION_MINOR "." #SCRIPT_VERSION_PATCH);
	SendRconCommand("gamemodetext "SERVER_MODE"");
	SendRconCommand("language "SERVER_LANGUAGE"");
	SendRconCommand("weburl "SERVER_WEBSITE"");

	SetWorldTime(23);
	SetWeather(0);
	DisableInteriorEnterExits();
	EnableStuntBonusForAll(false);
	UsePlayerPedAnims();

	// Init Vehicles
	LoadStaticVehiclesFromFile("vehicles/ls.txt");
	return 1;
}

public OnPlayerDeathEx(playerid, killerid, reason) {
	if(IsPlayerConnected(killerid)) {
		Player_GiveKill(killerid, 1, true);
		SendDeathMessage(killerid, playerid, reason);
	}

	Player_SetDeaths(playerid, 1, true);
	SendDeathMessage(INVALID_PLAYER_ID, playerid, reason);
	return 1;
}

// temporary fix for players not taking damage, although api should handle this when
// not in use.
public OnPlayerDamagePlayer(playerid, issuerid, &Float: amount, weaponid, bodypart)
{
	if(Player_GetClass(playerid) == Player_GetClass(issuerid) && Player_GetClass(playerid) != TEAM_CIVILIAN) {
		return 0; // no team damage.
	}

    return 1; // returning 0 will prevent user from taking damage (THIS IS A BIG FEATURE!)
}

// TEMP - MUST REMOVE!
CMD:kill(playerid, params[]) {
	SetPlayerHealth(playerid, 0.0);
	return 1;
}

CMD:killveh(playerid, params) {
	SetVehicleHealth(GetPlayerVehicleID(playerid), 0.0);
	return 1;
}