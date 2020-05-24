// Patrick Dave Subang (c) 2020 April 
// Github -> https://github.com/PatrickGTR

// Credits to these people, made the production easier.
// Southclaw, Y_Les, maddinatOr, SyS, Zeex, Slice, Lorenc


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


CMD:test1(playerid, params[]) {
	TextMenu_Create(playerid, "TestMenu1", "Title1");
	TextMenu_Add(playerid, "hello1");
	TextMenu_Add(playerid, "Hi1");
	TextMenu_Add(playerid, "What's up1");
	TextMenu_Show(playerid);
	return 1;
}

forward TestMenu1(playerid, listitem);
public TestMenu1(playerid, listitem) {
	switch(listitem) {
		case 1: {
			SendClientMessage(playerid, -1, "Hello1");
		}
		case 2: {
			SendClientMessage(playerid, -1, "Hi1");
		}
		case 3: {
			SendClientMessage(playerid, -1, "What's up1");
		}
	}
	return 1;
}

CMD:test(playerid, params[]) {
	TextMenu_Create(playerid, "TestMenu", "Title");
	TextMenu_Add(playerid, "hello");
	TextMenu_Add(playerid, "Hi");
	TextMenu_Add(playerid, "What's up");
	TextMenu_Show(playerid);
	return 1;
}

forward TestMenu(playerid, listitem);
public TestMenu(playerid, listitem) {
	switch(listitem) {
		case 1: {
			SendClientMessage(playerid, -1, "Hello");
		}
		case 2: {
			SendClientMessage(playerid, -1, "Hi");
		}
		case 3: {
			SendClientMessage(playerid, -1, "What's up");
		}
	}
	return 1;
}