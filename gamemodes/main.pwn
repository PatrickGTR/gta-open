// Patrick Dave Subang (c) 2020 April
// Github -> https://github.com/PatrickGTR

// Credits to these people, made the production easier.
// Southclaw, Y_Les, maddinatOr, SyS, Zeex, Slice, Lorenc


// Custom Callbacks
// OnPlayerLogin(playerid) -> called when player successfully logged in.
// OnPlayerRegister(playerid) -> called when player successfully registered.
// OnPlayerPassedBanCheck(playerid) -> called when player's ip/name/gcpi wasn't found in the ban database.
// OnPlayerSecondUpdate(playerid) -> called every second per player (like OnPlayerUpdate but not as intensive.)
// OnMySQLConnected() -> called when MySQL successfully connects. (this is used to setup tables & prepared statements)
// OnMySQLPreClose() -> called before MySQL disconnect (before mysql_close specifically.)
// OnServerWeekReset() -> called when the in-game week resets.
// OnServerDayReset() -> called when it's a new in-game day.

// Custom Functions
// Player_GiveScore(playerid, score, bool:save = false) -> give player a score.
// Player_RemoveScore(playerid, score) -> remove a score (automatically saved).

// TextdrawLetterSize Rule -> Thanks to DamianC
// Letter-size-y = letter-size-x * 4
// For a nice font display


#include <a_samp>

#define MYSQL_PREPARE_DEBUG 	(false)
#define MAX_STATEMENTS 100
#define SAMP_LOGGER_COMPAT

#define CGEN_MEMORY (20000) // needs looking at, no clue why we had to increase this. YSI said so.

// Set to true if table aren't set up.
#define SETUP_TABLE 			(false)
#define DISCORD					(false)
#define WEAPON_DEBUG			(true)

#include <constants>

#include <samp_bcrypt>
#include <a_mysql>
#include <YSI_Coding\y_inline>
#include <YSI_Coding\y_timers>
#include <mysql_prepared>
#include <map-zones>
#include <formatex>

#include <init>
#include <utils>
#include <anti-cheat> // w.i.p
#include <user-interface>
#include <server>
#include <account>
#include <player>
#include <houses>
#include <admin>
#include <system>
#include <chat> // chat & messaging
#include <cmds>
#include <mapping>
#include <tester>
#if DISCORD
	#include <discord>
#endif
#include <bank>
#include <gangs>


// Will be called after the rest ^
public OnGameModeInit() {
	SendRconCommand("hostname "#SERVER_NAME " v" #SCRIPT_VERSION_MAJOR "." #SCRIPT_VERSION_MINOR "." #SCRIPT_VERSION_PATCH);
	SendRconCommand("gamemodetext "SERVER_MODE"");
	SendRconCommand("language "SERVER_LANGUAGE"");
	SendRconCommand("weburl "SERVER_WEBSITE"");

	SetWorldTime(23);
	SetWeather(0);
	DisableInteriorEnterExits();
	EnableStuntBonusForAll(0);
	UsePlayerPedAnims();

	// Init Vehicles
	LoadStaticVehiclesFromFile("vehicles/ls_airport.txt");
	LoadStaticVehiclesFromFile("vehicles/ls_gen_inner.txt");
	LoadStaticVehiclesFromFile("vehicles/ls_gen_outer.txt");
	LoadStaticVehiclesFromFile("vehicles/ls_law.txt");
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason) {
	if(IsPlayerConnected(killerid)) {
		Player_GiveKill(killerid, 1, true);
	}
	if(IsPlayerConnected(playerid)) {
		Player_SetDeaths(playerid, 1, true);
	}
	return 1;
}

// temporary fix for players not taking damage, although api should handle this when
// not in use.
public OnPlayerTakePlayerDamage(playerid, issuerid, &Float: amount, weaponid, bodypart )
{
	if(Player_GetClass(playerid) == Player_GetClass(issuerid) && Player_GetClass(playerid) != TEAM_CIVILIAN) {
		return 0; // no team damage.
	}

    return 1; // returning 0 will prevent user from taking damage (THIS IS A BIG FEATURE!)
}