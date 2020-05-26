// Patrick Dave Subang (c) 2020 April 
// Github -> https://github.com/PatrickGTR

// Credits to these people, made the production easier.
// Southclaw, Y_Les, maddinatOr, SyS, Zeex, Slice, Lorenc


// Custom Callbacks
// OnPlayerLogin(playerid) -> called when player successfully logged in.
// OnPlayerRegister(playerid) -> called when player successfully registered.



#include <a_samp>

#define MYSQL_PREPARE_DEBUG 	(false)

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

CMD:gmoney(playerid, params[]) {
	GivePlayerMoney(playerid, 100000);
	return 1;
}

#include <YSI_Coding\y_timers>
new timer = 300;
new Timer:timer_test;

CMD:starttime(playerid, params[]) {
	timer_test = repeat TestTimer(playerid);
	return 1;
}

timer TestTimer[1000](playerid) {

	if(timer <= 0) {
		stop timer_test;
	}

	UI_TimeLeft(playerid, timer);
	timer --;
	return 1;
}

// temporary fix for players not taking damage, although api should handle this when
// not in use.
public OnPlayerTakePlayerDamage( playerid, issuerid, &Float: amount, weaponid, bodypart )
{
    return 1; // returning 0 will prevent user from taking damage (THIS IS A BIG FEATURE!)
}