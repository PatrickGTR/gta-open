// Patrick Dave Subang (c) 2020 April 
// Github -> https://github.com/PatrickGTR

// Credits to these people, made the production easier.
// Southclaw, Y_Les, maddinatO, SyS, Zeex, Slice, Lorenc


#include <a_samp>

#define MYSQL_PREPARE_DEBUG 	(true)

// Set to true if table aren't set up.
#define SETUP_TABLE 			(true)

#include <constants>
#include <init>

#include <utils>
#include <anti-cheat_main> // w.i.p
#include <server>
#include <user-interface>
#include <account>
#include <player>
#include <admin> 
#include <chat> // chat & messaging

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

	new money = strval(params);

	GivePlayerMoney(playerid, money);
	return 1;
}