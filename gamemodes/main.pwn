// Patrick Dave Subang (c) 2020 April 
// Github -> https://github.com/PatrickGTR

// Credits to these people, made the production easier.
// Southclaw, Y_Les, maddinatOr, SyS, Zeex, Slice, Lorenc


// Custom Callbacks
// OnPlayerLogin(playerid) -> called when player successfully logged in.
// OnPlayerRegister(playerid) -> called when player successfully registered.
// OnPlayerPassedBanCheck(playerid) -> called when player's ip/name/gcpi wasn't found in the ban database.
// OnPlayerSecondUpdate(playerid) -> called every second per player (like OnPlayerUpdate but not as intensive.)

// TextdrawLetterSize Rule -> Thanks to DamianC
// Letter-size-y = letter-size-x * 4
// For a nice font display

#include <a_samp>

#define MYSQL_PREPARE_DEBUG 	(false)
#define MAX_STATEMENTS 32

// Set to true if table aren't set up.
#define SETUP_TABLE 			(false)	

#include <constants>
#include <init>
#include <utils>
#include <anti-cheat_main> // w.i.p
#include <server>
#include <user-interface>
#include <account>
#include <player>
#include <houses>
#include <admin> 
#include <system>
#include <chat> // chat & messaging
#include <cmds>


// Will be called after the rest ^
public OnGameModeInit() {
	SendRconCommand("hostname "SERVER_NAME" v"SERVER_VERSION"");
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


CMD:gmoney(playerid) {
	GivePlayerMoney(playerid, 1000000);
	SendMsgF(playerid, -1, "Received %m", 1000000);
	return 1;
}

CMD:givewanted(playerid) {
	PLAYER_SetPlayerWantedLevel(playerid, 3);
	return 1;
}

CMD:c4(playerid, params[]) {
	Player_SetC4(playerid, 10);
	return 1;
}

// temporary fix for players not taking damage, although api should handle this when
// not in use.
public OnPlayerTakePlayerDamage(playerid, issuerid, &Float: amount, weaponid, bodypart )
{
    return 1; // returning 0 will prevent user from taking damage (THIS IS A BIG FEATURE!)
}